#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct find_output
{
	int numlines;
	char** lines;
}find_output;

void usage()
{
	printf("This program is a work in progress... please wait...\n");
}

struct find_output* CreateOutput(int numlines)
{
	struct find_output* out = (struct find_output*)(malloc(sizeof(struct find_output)));
	out->numlines = numlines;
	out->lines = (char**)(malloc(sizeof(char*)));
	return out;
}

void DestroyOutput(struct find_output* find_output)
{
	//free(find_output->lines);
	free(find_output);
}

int main(int argc, char* argv[])
{
	struct find_output* out = CreateOutput(10);
	usage();	//TODO
	//TODO: Pretty much be BSD grep with a different name.
	DestroyOutput(out);
	return 0;
}

