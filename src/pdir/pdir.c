#include <abstract.h>
#include <stdio.h>

int main()
{
	char cwd[2048];
	GetWorkingDirectory(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return 0;
}
