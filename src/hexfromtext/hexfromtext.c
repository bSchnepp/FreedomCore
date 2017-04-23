#include <abstract.h>

#include <string.h>
#include <stdio.h>

//TODO: read from files!


char print_decimal;
char print_hex;

int open_flags = 0;
int content_ptr = 0;


//Gets the values and does the printing. This is a separate function so we can add features later.
void print_stuff(char* string)
{
	int size = strlen(string);
	int start = 0;

	if (print_decimal)
	{
		for (int i = start; i < size; i++)
		{
			printf("%d ", string[i]);
		}
	}
	
	//This is for when we do things like binary and stuff.
	if (open_flags)
	{
		printf("\n");
	}
	
	if (print_hex)
	{
		for (int i = start; i < size; i++)
		{
			printf("0x%x ", string[i]);
		}
	}
	
	//No more possible flags... newlining.
	printf("\n");
}


int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-h"))
		{
			print_hex = 1;
			content_ptr++;
			open_flags++;
		}
		else if (!strcmp(argv[i], "-d"))
		{
			print_decimal = 1;
			content_ptr++;
			open_flags++;
		}
	}

	//Manually putting int -s for the string's location if it's NOT at the end.
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-s"))
		{
			content_ptr = i;
		}
	}
	print_stuff(argv[content_ptr+1]);

	return 0;
}
