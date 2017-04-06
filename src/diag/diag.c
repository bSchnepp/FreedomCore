#include <stdio.h>
#include <string.h>

//Command line tool that just spits out system diagnostics.
//Ie, RAM, CPU, num of open processes, maybe graphics adapter, etc.

void usage()
{
	printf("Usage:	\n\
	Type in the command for an overview of basic system information. \n\
	Flags: \n\
		-o for operating system information \n\
		-p for information on running programs \n\
		-? for this message.	\n");
}

void default_info()
{
	//TODO
}

void graphics_info()
{
	//TODO
}

void top_info()
{
	//TODO
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		default_info();
	}
	else if (!strcmp(argv[1], "-?"))
	{
		usage();
		return 0;
	}
	else if (!strcmp(argv[1], "-o"))
	{
			
	}
	else if (!strcmp(argv[1], "-p"))
	{
			
	}
	else
	{
		return -3;
	}
}
