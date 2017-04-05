#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char by;
	FILE* source = fopen(argv[1], "r");
	FILE* dest   = fopen(argv[2], "w");
	if (source == NULL)
	{
		printf("Invalid files attempted to be copied.\n");
		fclose(source);
		if (dest != NULL)
		{
			fclose(dest);
			//Figure out a cleaner way to write this later.
		}	
		return -2;
	}
	while ((by = fgetc(source)) != EOF)
	{
		fputc(by, dest);
	}
	fclose(source);
	fclose(dest);
	return 0;
}
