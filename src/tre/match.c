#include <stdio.h>
#include "tre.h"

#define TRE_IMPLEMENTATION
#define TRE_SILENT

int main(int argc, char **argv)
{
	tre_comp tregex;
	const char *string;
	const char *end;
	const char *start;

	if (argc < 3)
	{
		printf("Usage: %s pattern string\n", argv[0]);
		return -1;
	}

	tre_compile(argv[1], &tregex);
	tre_print(&tregex);
	
	string = argv[2];
	start = tre_match(&tregex, string, &end);
	
	if (start)
	{
		printf("match start: %ld match end: %ld\n", start - string, end - string);
		return 1;
	}
	else
	{
		printf("no match\n");
		return 0;
	}
}
