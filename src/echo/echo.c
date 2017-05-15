#include <stdio.h>

int main(int argc, char* argv[])
{
	for (long int i = 1; i < argc; i++)
	{
		printf("%s ", argv[i]);
	}
	puts("");
	return 0;
}
