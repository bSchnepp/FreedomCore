#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <abstract.h>

#define FIND_VERSION 0
#define FIND_VERSION_MINOR 0
#define FIND_VERSION_MINOR_PATCH 3

#define NEW_LINE 10	//Newline ASCII code (decimal)!!


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
uint64_t num_of_newlines = 0;

void usage()
{
	printf("This program is a work in progress... please wait...\n");
	printf("Flags:\n");
	printf("\t\"-i\" for all lines NOT containing the string. (inverse)\n"); 
}

int* check_newlines(struct find_buffer* buffer)
{
	//This is __terribly__ slow. We'll fix this later. 
	int* positions = (int*)(malloc(sizeof(int) * buffer->buffer_size));	//MASSIVE array!!!! FIXME!!
	uint64_t num_pos_newlines = 0;
	for (uint64_t i = 0; i < buffer->buffer_size; i++)
	{
		if (buffer->data[i] == NEW_LINE)
		{
			positions[num_pos_newlines] = i;
			num_pos_newlines++;	
		}
	}
	int* ret_array = (int*)(malloc(num_pos_newlines * sizeof(int)));
	for (uint64_t i = 0; i < num_pos_newlines; i++)
	{
		ret_array[i] = positions[i];
	}
	free(positions);
	num_of_newlines = num_pos_newlines;
	return ret_array;
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
		printf("%i.%i.%i\n", FIND_VERSION, FIND_VERSION_MINOR, FIND_VERSION_MINOR_PATCH); 
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
		//Dirty hack we can do is actually create a cache file, and re-run ourself with the cache file, post results, and delete the temp file.
		FILE* cache = fopen("$freedom-find_$", "wb");
		fflush(cache);		
		fclose(cache);

		//main(offset + 2, /* TODO: Parameters!!! */ "$freedom-find_$");	//2, one because the name itself is 0, and the second because we're adding the file.
 		//Call ourself with the same parameters, but with the file instead of the wall of text...		
		
		remove("$freedom-find_$");	//'$' is going to be the hidden character for WayFS, which I'm working out how to make work. 
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
	fclose(file);	//Terminate the file since we no longer need it, and have what we want cached in memory.

	//Do our work here...
	int* line_pos = check_newlines(buffer);	//This gets an array of where all the newlines are.
	// Find lines.

	int sz = (buffer->data[buffer->buffer_size-1] == NEW_LINE) ? 
		  num_of_newlines : 
		  num_of_newlines + 1;	//Is there any data after the last newline?
	for (uint64_t i = 1; i < sz; i++)
	{
		char* line;
		if ((sz > num_of_newlines) && (i > num_of_newlines))
		{
			//Position to end of the file.
			uint64_t size_diff = strlen(buffer->data) - strlen(buffer->data + line_pos[i - 1]);
			line = memcpy(line, (buffer->data) + line_pos[i - 1], size_diff);
		}
		else
		{
			//Position between the two newlines.
			uint64_t size_diff = strlen(buffer->data + line_pos[i - 1]) - strlen(buffer->data + line_pos[i]);
			
			line = (char*)(malloc(size_diff));
			memcpy(line, ((buffer->data) + (line_pos[i])), size_diff);
		}
		if (strstr(line, argv[2 + offset]))
		{
			printf("%s\n", line);
		}
		free(line);
	}

	//We're done, and dumped what we wanted to stdout.
	free(buffer->data);
	free(buffer);
	return -2;
}

