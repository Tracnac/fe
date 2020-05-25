#include "string.h"
#include "tre.h"

#ifndef TRE_SILENT
#include "stdio.h"
#include "stdarg.h"
#endif

static int tre_err(const char *format, ...)
{
#ifdef TRE_SILENT
	(void) format;
#else
	fputs("Error: ", stderr);
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	fputs("\n", stderr);
	fflush(stderr);
#endif
	return 0;
}

TRE_DEF const char *tre_compile_match(const char *pattern, const char *text, const char **end)
{
	tre_comp tregex = {0};
	if (!tre_compile(pattern, &tregex))
	{
		tre_err("Compiling pattern failed");
		return 0;
	}
	
	return tre_match(&tregex, text, end);
}

static const char *matchpattern(const tre_node *nodes, const char *text, const char *tend);

TRE_DEF const char *tre_nmatch(const tre_comp *tregex, const char *text, unsigned tlen, const char **end)
{
	const char *mend;
	const tre_node *nodes = tregex->nodes;
	const char *tend = text + tlen;

	if (!tregex || !text || !tlen)
	{
		tre_err("NULL text or tre_comp");
		return 0;
	}
	
	if (nodes->type == TRE_BEGIN)
	{
		mend = matchpattern(nodes + 1, text, tend);
		if (mend)
		{
			if (end)
				*end = mend;
			return text;
		}
		return 0;
	}
	
	do
	{
		mend = matchpattern(nodes, text, tend);
		if (mend)
		{
/* 			if (!*text) Fixme: ???
			     return 0; */
			if (end)
				*end = mend;
			return text;
		}
	}
	while (tend > text++);
	
	return 0;
}

TRE_DEF const char *tre_match(const tre_comp *tregex, const char *text, const char **end)
{
	return tre_nmatch(tregex, text, strlen(text), end);
}

#define TRE_ISMETA(c) ((c=='s')||(c=='S')||(c=='w')||(c=='W')||(c=='d')||(c=='D'))

TRE_DEF int tre_ncompile(const char *pattern, unsigned plen, tre_comp *tregex)
{
	tre_node *tnode = tregex->nodes;
	char *buf = tregex->buffer;
	unsigned buflen = sizeof tregex->buffer;
	char quable = 0;
	char temp;
	
	unsigned idx = 0;
	/* for parsing numbers in {m,n} */
	unsigned long val;
	/* index into pattern */
	unsigned i = 0;
	/* index into tnode */
	unsigned j = 0;

	if (!tregex || !pattern || !plen)
		return tre_err("NULL/empty string or tre_comp");

	/* is the last node quantifiable= sizeof tregex->buffer; */
	
	while (i < plen && (j + 1 < TRE_MAX_NODES))
	{
		switch (pattern[i])
		{
		/* Meta-characters */
		case '^': quable = 0; tnode[j].type = TRE_BEGIN; break;
		case '$': quable = 0; tnode[j].type = TRE_END;   break;
		case '.': quable = 1; tnode[j].type = TRE_DOT;   break;
		case '*':
			if (quable == 0)
				return tre_err("Non-quantifiable before *");
			quable = 0;
			tnode[j].type = (pattern[i + 1] == '?') ? (i++, TRE_LSTAR) : TRE_STAR; break;
		case '+':
			if (quable == 0)
				return tre_err("Non-quantifiable before +");
			quable = 0;
			tnode[j].type = (pattern[i + 1] == '?') ? (i++, TRE_LPLUS) : TRE_PLUS; break;
		case '?':
			if (quable == 0)
				return tre_err("Non-quantifiable before ?");
			quable = 0;
			tnode[j].type = (pattern[i + 1] == '?') ? (i++, TRE_LQMARK) : TRE_QMARK; break;
			
		/* Escaped characters */
		case '\\':
		{
			quable = 1;
			if (++i >= plen)
				return tre_err("Dangling \\");
				
			switch (pattern[i])
			{
			/* Meta-character: */
			case 'd': tnode[j].type = TRE_DIGIT;  break;
			case 'D': tnode[j].type = TRE_NDIGIT; break;
			case 'w': tnode[j].type = TRE_ALPHA;  break;
			case 'W': tnode[j].type = TRE_NALPHA; break;
			case 's': tnode[j].type = TRE_SPACE;  break;
			case 'S': tnode[j].type = TRE_NSPACE; break;
			
			/* Not in [dDwWsS] */
			default: tnode[j].type = TRE_CHAR; tnode[j].u.ch = pattern[i]; break;
			}
		} break;
		
		/* Character class */
		case '[':
		{
			quable = 1;
			
			/* Look-ahead to determine if negated */
			tnode[j].type = (pattern[i + 1] == '^') ? (i++, TRE_NCLASS) : TRE_CLASS;
			tnode[j].u.cc = buf + idx;
			
			/* Copy characters inside [...] to buffer */
			while (pattern[++i] != ']' && i < plen)
			{
				temp = 0;
				if (pattern[i] == '\\')
				{
					if (++i >= plen)
						return tre_err("Dangling '\\' in class");
						
					/* Only escape metachars and escape, omit escape for others */
					temp = TRE_ISMETA(pattern[i]);
					if (temp || pattern[i] == '\\')
					{
						if (idx > buflen - 2)
							return tre_err("Buffer overflow in in class", i - 1);
						buf[idx++] = '\\';
					}
				}
				
				if (idx > buflen - 2)
					return tre_err("Buffer overflow in class");
				buf[idx++] = pattern[i];
				
				/* Check if it is a range */
				if (temp)
					/* metachar */
					continue;
					
				if (pattern[i + 1] != '-' || i + 2 >= plen || pattern[i + 2] == ']')
					/* not '-' or "-"! or "-]" */				
					continue;
					
				temp = (pattern[i + 2] == '\\');
				if (temp && (i + 3 >= plen || TRE_ISMETA(pattern[i + 3])))
				 /* "-\\"! or "-\\w" */
					continue;
					
				/* Validate range */
				temp = temp ? pattern[i + 3] : pattern[i + 2];
				if (temp < pattern[i])
					return tre_err("Incorrect range in class");
				/* if (idx > buflen - 2)
					return tre_err("Buffer overflow at range - in class");
				buf[idx++] = pattern[++i]; '-' */
			}
			
			if (pattern[i] != ']')
				return tre_err("Non terminated class");
				
			buf[idx++] = 0;
		} break;
		
		/* Quantifier */
		case '{':
		{
			if (quable == 0)
				return tre_err("Non-quantifiable before {m,n}");
			quable = 0;
			
			i++;
			val = 0;
			do
			{
				if (i >= plen || pattern[i] < '0' || pattern[i] > '9')
					return tre_err("Non-digit min value in quantifier");
				val = 10 * val + (unsigned) (pattern[i++] - '0');
			}
			while (pattern[i] != ',' && pattern[i] != '}');
			
			if (val > TRE_MAXQUANT)
				return tre_err("Min value too big in quantifier");
			tnode[j].u.mn[0] = val;
			
			if (pattern[i] == ',')
			{
				if (++i >= plen)
					return tre_err("Dangling ',' in quantifier");
				if (pattern[i] == '}')
				{
					val = TRE_MAXQUANT;
				}
				else
				{
					val = 0;
					while (pattern[i] != '}')
					{
						if (i >= plen || pattern[i] < '0' || pattern[i] > '9')
							return tre_err("Non-digit max value in quantifier");
						val = 10 * val + (unsigned) (pattern[i++] - '0');
					}
					
					if (val > TRE_MAXQUANT || val < tnode[j].u.mn[0])
						return tre_err("Max value too big or less than min value in quantifier");
				}
			}
			tnode[j].type = (i + 1 < plen && pattern[i + 1] == '?') ? (i++, TRE_LQUANT) : TRE_QUANT;
			tnode[j].u.mn[1] = val;
		} break;
		
		/* Regular characters */
		default: quable = 1; tnode[j].type = TRE_CHAR; tnode[j].u.ch = pattern[i]; break;
		}
		i++;
		j++;
	}
	/* 'TRE_NONE' is a sentinel used to indicate end-of-pattern */
	tnode[j].type = TRE_NONE;
	
	return 1;
}

TRE_DEF int tre_compile(const char *pattern, tre_comp *tregex)
{
	return tre_ncompile(pattern, strlen(pattern), tregex);
}

#define TRE_MATCHDIGIT(c) ((c >= '0') && (c <= '9'))
#define TRE_MATCHALPHA(c) ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))
#define TRE_MATCHSPACE(c) ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r') || (c == '\f') || (c == '\v'))
#define TRE_MATCHALNUM(c) ((c == '_') || TRE_MATCHALPHA(c) || TRE_MATCHDIGIT(c))

static int matchmetachar(char c, char mc)
{
	switch (mc)
	{
	case 'd': return  TRE_MATCHDIGIT(c);
	case 'D': return !TRE_MATCHDIGIT(c);
	case 'w': return  TRE_MATCHALNUM(c);
	case 'W': return !TRE_MATCHALNUM(c);
	case 's': return  TRE_MATCHSPACE(c);
	case 'S': return !TRE_MATCHSPACE(c);
	default:  return (c == mc);
	}
}

/* note: compiler makes sure '\\' is followed by one of 'dDwWsS\\' */
static int matchcharclass(char c, const char *str)
{
	char rmax;
	while (*str != '\0')
	{
		if (str[0] == '\\')
		{
			if (matchmetachar(c, str[1]))
				return 1;
			str += 2;
			if (TRE_ISMETA(*str))
				continue;
		}
		else
		{
			if (c == *str)
				return 1;
			str += 1;
		}
		
		if (*str != '-' || !str[1])
			continue;
		rmax = (str[1] == '\\');
		if (rmax && TRE_ISMETA(str[2]))
			continue;
			
		rmax = rmax ? str[2] : str[1];
		if (c >= str[-1] && c <= rmax)
			return 1;
		str++;
		
	}
	
	return 0;
}


#ifndef TRE_DOTANY
#define TRE_MATCHDOT(c)   ((c != '\n') && (c != '\r'))
#else
#define TRE_MATCHDOT(c)   (1)
#endif

static int matchone(const tre_node *tnode, char c)
{
	switch (tnode->type)
	{
	case TRE_CHAR:   return (tnode->u.ch == c);
	case TRE_DOT:    return  TRE_MATCHDOT(c);
	case TRE_CLASS:  return  matchcharclass(c, tnode->u.cc);
	case TRE_NCLASS: return !matchcharclass(c, tnode->u.cc);
	case TRE_DIGIT:  return  TRE_MATCHDIGIT(c);
	case TRE_NDIGIT: return !TRE_MATCHDIGIT(c);
	case TRE_ALPHA:  return  TRE_MATCHALNUM(c);
	case TRE_NALPHA: return !TRE_MATCHALNUM(c);
	case TRE_SPACE:  return  TRE_MATCHSPACE(c);
	case TRE_NSPACE: return !TRE_MATCHSPACE(c);
	default: return 0;
	}
}

#undef TRE_MATCHDIGIT
#undef TRE_MATCHALPHA
#undef TRE_MATCHSPACE
#undef TRE_MATCHALNUM
#undef TRE_MATCHDOT

static const char *matchquant_lazy(const tre_node *nodes, const char *text, const char *tend,
    unsigned min, unsigned max)
{
	const char *end;
	max = max - min;
	while (min && text < tend && matchone(nodes, *text)) { text++; min--; }
	
	if (min)
		return 0;
	
	if ((end = matchpattern(nodes + 2, text, tend)))
		return end;
	
	while (max && text < tend && matchone(nodes, *text))
	{
		text++; max--;
		if ((end = matchpattern(nodes + 2, text, tend)))
			return end;
	}
	
	return 0;
}

static const char *matchquant(const tre_node *nodes, const char *text, const char *tend,
    unsigned min, unsigned max)
{
	const char *end, *start = text + min;
	while (max && text < tend && matchone(nodes, *text)) { text++; max--; }
	
	while (text >= start)
	{
		if ((end = matchpattern(nodes + 2, text--, tend)))
			return end;
	}
	
	return 0;
}

/* Iterative matching */
static const char *matchpattern(const tre_node *nodes, const char *text, const char *tend)
{
	do
	{
		if (nodes[0].type == TRE_NONE)
			return text;
			
		if ((nodes[0].type == TRE_END) && nodes[1].type == TRE_NONE)
			return (text == tend) ? text : 0;
			
		switch (nodes[1].type)
		{
		case TRE_QMARK:
			return matchquant(nodes, text, tend, 0, 1);
		case TRE_LQMARK:
			return matchquant_lazy(nodes, text, tend, 0, 1);
		case TRE_QUANT:
			return matchquant(nodes, text, tend, nodes[1].u.mn[0], nodes[1].u.mn[1]);
		case TRE_LQUANT:
			return matchquant_lazy(nodes, text, tend, nodes[1].u.mn[0], nodes[1].u.mn[1]);
		case TRE_STAR:
			return matchquant(nodes, text, tend, 0, TRE_MAXPLUS);
		case TRE_LSTAR:
			return matchquant_lazy(nodes, text, tend, 0, TRE_MAXPLUS);
		case TRE_PLUS:
			return matchquant(nodes, text, tend, 1, TRE_MAXPLUS);
		case TRE_LPLUS:
			return matchquant_lazy(nodes, text, tend, 1, TRE_MAXPLUS);
		}
	}
	while (text < tend && matchone(nodes++, *text++));
	
	return 0;
}

void tre_print(const tre_comp *tregex)
{
#ifdef TRE_SILENT
	(void) tregex;
#else
#define X(A) #A,
	static const char *tre_typenames[] = { TRE_TYPES_X };
#undef X
	
	if (!tregex)
	{
		printf("NULL compiled regex detected\n");
		return;
	}
	
	const tre_node *tnode = tregex->nodes;
	int i;
	for (i = 0; i < TRE_MAX_NODES; ++i)
	{
		if (tnode[i].type == TRE_NONE)
			break;
	
		printf("type: %s", tre_typenames[tnode[i].type]);
		if (tnode[i].type == TRE_CLASS || tnode[i].type == TRE_NCLASS)
		{
			printf(" \"%s\"", tnode[i].u.cc);
		}
		else if (tnode[i].type == TRE_QUANT || tnode[i].type == TRE_LQUANT)
		{
			printf(" {%d,%d}", tnode[i].u.mn[0], tnode[i].u.mn[1]);
		}
		else if (tnode[i].type == TRE_CHAR)
		{
			printf(" '%c'", tnode[i].u.ch);
		}
		printf("\n");
	}
/* TRE_SILENT */
#endif
}

#undef TRE_TYPES_X
