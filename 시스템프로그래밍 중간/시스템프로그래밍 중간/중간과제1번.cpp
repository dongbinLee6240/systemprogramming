#include <stdio.h>	
#include <stdlib.h>

int main()
{
	char* getenv(const char* name);
	printf("ComputerName=%s\n", getenv("COMPUTERNAME"));
}