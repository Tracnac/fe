/* Public Domain Tiny Regular Expressions Library
Forked from https://github.com/kokke/tiny-regex-c

Supports:
---------
  '^'        Start anchor, matches start of string
  '$'        End anchor, matches end of string
---------
  '*'        Asterisk, match zero or more (greedy, *? lazy)
  '+'        Plus, match one or more (greedy, +? lazy)
  '{m,n}'    Quantifier, match min. 'm' and max. 'n' (greedy, {m,n}? lazy)
  '{m}'                  exactly 'm'
  '{m,}'                 match min 'm' and max. MAX_QUANT
  '?'        Question, match zero or one (greedy, ?? lazy)
---------
  '.'        Dot, matches any character except newline (\r, \n)
  '[abc]'    Character class, match if one of {'a', 'b', 'c'}
  '[^abc]'   Inverted class, match if NOT one of {'a', 'b', 'c'}
  '[a-zA-Z]' Character ranges, the character set of the ranges { a-z | A-Z }
  '\s'       Whitespace, \t \f \r \n \v and spaces
  '\S'       Non-whitespace
  '\w'       Alphanumeric, [a-zA-Z0-9_]
  '\W'       Non-alphanumeric
  '\d'       Digits, [0-9]
  '\D'       Non-digits
  '\X'       Character itself; X in [^sSwWdD] (e.g. '\\' is '\')
---------
 */

#ifndef TRE_H_INCLUDE
#define TRE_H_INCLUDE

#ifndef TRE_STATIC
#define TRE_DEF extern
#else
#define TRE_DEF static
#endif

/* Max in {m,n} - must be < ushrt_max - see "struct tre_node" */
#define TRE_MAXQUANT  1024
/* For + and * */
#define TRE_MAXPLUS  40000

enum TRE_TYPES { TRE_NONE, TRE_BEGIN, TRE_END, TRE_QUANT, TRE_LQUANT, \
       TRE_QMARK, TRE_LQMARK, TRE_STAR, TRE_LSTAR, TRE_PLUS, \
			 TRE_LPLUS, TRE_DOT, TRE_CHAR, TRE_CLASS, TRE_NCLASS, \
			 TRE_DIGIT, TRE_NDIGIT, TRE_ALPHA, TRE_NALPHA, TRE_SPACE, TRE_NSPACE };

/* Max number of regex nodes in expression. */
#define TRE_MAX_NODES    64
/* Max length of character-class buffer. */
#define TRE_MAX_BUFLEN  128
/* disable inclusion of stdio and printing */
#define TRE_SILENT 
/* dot matches anything including newline */
/* #define TRE_DOTANY */

typedef struct tre_node tre_node;
typedef struct tre_comp tre_comp;

struct tre_node
{
	unsigned char  type;
	union
	{
    /* character */
		char  ch;
    /* character class buffer */
		char *cc;
    /* {m,n} quantifier */
		unsigned short mn[2];
	} u;
};

struct tre_comp
{
	tre_node nodes[TRE_MAX_NODES];
	char buffer[TRE_MAX_BUFLEN];
};

/* Compile regex string pattern as tre_comp struct tregex */
TRE_DEF int tre_compile(const char *pattern, tre_comp *tregex);

/* Match tregex in text and return the match start or null if there is no match
If end is not null set it to the match end */
TRE_DEF const char *tre_match(const tre_comp *tregex, const char *text, const char **end);

/* Same but compiles pattern then matches */
TRE_DEF const char *tre_compile_match(const char *pattern, const char *text, const char **end);

/* Print the pattern */
TRE_DEF void tre_print(const tre_comp *tregex);

/* TRE_H_INCLUDE */
#endif
