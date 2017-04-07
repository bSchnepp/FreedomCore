#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <abstract.h>

#define FIND_VERSION 0
#define FIND_VERSION_MINOR 0
#define FIND_VERSION_MINOR_PATCH 1


/* Struct defs */

struct find_buffer
{
	uint64_t buffer_size;
	char* data;
}find_buffer;


/*
 *	Copy the stuff into a buffer
 *	Search through the buffer
 *	If the requested string is found,
 *	We search for the previous newline and the next newline
 *	Then print out everything between that.
 */

bool invert = 0;

void usage()
{
	printf("This program is a work in progress... please wait...\n");
	printf("Flags:\n");
	printf("\t\"-i\" for all lines NOT containing the string. (inverse)\n"); 
}

int main(int argc, char* argv[])
{
	//TODO:
	//Check if fopening argv[1] is invalid. If it is, then we assume the rest is in fact, piped content.
	//Remember that we're basically a DOS-ified grep, sooo...
	
	//These options should never have useful finding information attached to them.	
	if (argc < 2)
	{
		usage();
		return 0;
	}	
	if  (!strcmp(argv[1], "-?")) //Check if the user is wanting help...
	{
		usage();
		return 0;
	}
	if (!strcmp(argv[1], "--version")) //Check if the user is wanting help...
	{
		printf("%i.%i.%i", FIND_VERSION, FIND_VERSION_MINOR, FIND_VERSION_MINOR_PATCH); 
		return 0;
	}

	int offset = 0;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-i"))
		{
			offset++;
		}
	}

	FILE* file = fopen(argv[offset + 1], "rb");
	if (file == NULL)
	{
		//Code for handling the rest as being direct input...
		return 0;
	}
	
	fseek(file, 0, SEEK_END);
	struct find_buffer* buffer = (struct find_buffer*)(malloc(sizeof(find_buffer)));
	buffer->buffer_size = (uint64_t)ftell(file);
	rewind(file);
	buffer->data = (char*)(calloc(1, buffer->buffer_size));
	
	if (buffer->data == NULL)
	{
		fprintf(stderr, "Memory allocation failed.");
		printf("Invalid file size. Are you sure you have enough free RAM?");
		return -3;
	}
	fread(buffer->data, 1, buffer->buffer_size, file);
	fclose(file);

	//Do our work here...

	free(buffer->data);
	free(buffer);
	return -2;
}

