#include <stdlib.h>
#include <stdio.h>
#include "whoami.h"

int main(int argc, char* argv[])
{
	GET_USERNAME_MACRO	//Dirty hack, but keeps the POSIX away...

	if (pw)
	{
		printf("%s\n", GET_USERNAME_AS_STRING);
		return 0;
	}
	printf("Unknown error attempting to get username.");
	return -2;
}
