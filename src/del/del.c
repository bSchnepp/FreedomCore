#include <stdio.h>
#include <string.h>

void usage()
{
	printf("%s\n", "Add the name of the file you want to delete as an argument.");
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return -2;
	}
	if (!strcmp(argv[1], "-?"))
	{
		usage();
		return 0;
	}
	int success = remove(argv[1]);
	if (success)
	{
		printf("%s\n", "Could not delete file.");
		return success;	
	}
	else
	{
		return 0;
	}
}
