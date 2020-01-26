#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if ((!fork()) ^ fork())
	{
		printf("+");
		exit(0);
	}
	return 0;
}
