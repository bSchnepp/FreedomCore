#include <stdio.h>
#include <string.h>

void usage()
{
	printf("Usage: \n\
                Place the file name of the file to display as an argument.	\n\
		Example:	\n\
		disp file.txt\n");
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		usage();
		return -2;
	}
	else if (!(strcmp(argv[1], "-?")))
	{
		usage();
		return -2;
	}

	FILE* file = fopen(argv[1], "r");
	if (file == 0)
	{
		//Something went wrong trying to open the file... Let's guess.
		printf("Invalid file to open. Input '-?' for usage info.\n");
		return -3;
	}

	int ch;	//Place to store character
	while ((ch = fgetc(file)) != EOF)
	{
		printf("%c", ch);
	}
	fclose(file);
	return 0;
}

