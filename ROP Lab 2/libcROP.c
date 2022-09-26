// compile with gcc libcROP.c -o libcROP -Wl,-z,relro -Wl,-ldl -fno-stack-protector -O0
// the last part is linker flags for making this program relocatable/readonly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <dlfcn.h>

void writeLogfile()
{

	int bufferSize = 256;
	char buf[sizeof(bufferSize)];
	int inputCount = 0;
	int result = 0;

	printf("Enter your note up to 255 chars\n");

	gets(buf);	// safer than gets

	FILE *fp = fopen("logfile", "a+");
	if (fp == NULL)
	{
		puts("Error opening logfile\n");
	}
	else
	{
		fputs(buf, fp);
	}

	fclose(fp);
}

void printValAtAddr()
{
	int bufferSize = 19;
	char buffer[19] = {0};
	void* result;

	puts("What is the address? (enter up to 18 chars): ");
	result = fgets(buffer, bufferSize, stdin);

	if (result == NULL) 
	{
		puts("bad input\n");
		return;	    
	}
	else
	{
		int pos = strlen(buffer);
		buffer[pos-1] = '\0';
	}
	
	unsigned int* addr = (unsigned int*) strtol(buffer, NULL, 16);

	printf("%08x", *addr);
}

void printAddr()
{
	int bufferSize = 30;
	char buffer[30] = {0};
	void* result;

	puts("What is the name of the function? (enter up to 30 chars): ");
	result = fgets(buffer, bufferSize, stdin);

	if (result == NULL) 
	{
		puts("bad input\n");
		return;	    
	}
	else
	{
		int pos = strlen(buffer);
		buffer[pos-1] = '\0';
	}

	// see http://pubs.opengroup.org/onlinepubs/009604499/functions/dlsym.html for more info
	void* handle;
	double (*function_pointer)(double);


	/* open the needed object */
	handle = dlopen("/lib/x86_64-linux-gnu/libc.so.6", RTLD_LOCAL | RTLD_LAZY);	// symlink to current x64 libc


	/* find the address of function */
	*(void **) (&function_pointer) = dlsym(handle, buffer);
	printf("address is: %p\n", function_pointer);

	dlclose(handle);

}

void main() {
	int end = 0;
	int input = 0;
	int result = 0;
	char c;

	while(end == 0)
	{
		int inputCount = 0;

		printf("\n************************************************\n");
		printf("DoStuff is a program which lets a user do stuff.\n");
		printf("What would you like to do?\n");
		printf("1. Write to logfile\n");
		printf("2. Print address of libc function\n");
		printf("3. Print bytes at address (must enter valid address)\n");
		printf("4. Exit\n");
		printf("************************************************\n");

		result = scanf("%d", &input);
		while ((c = getchar()) != '\n' && c != EOF);	//get rid of garbage

		if (result == 0 || result == EOF || input <= 0 || input > 4)
		{
			printf("Bad input, try again\n");
		}
		else if (input == 1)
		{
			writeLogfile();
		}
		else if (input == 2)
		{
			printAddr();
		}
		else if (input == 3)
		{
			printValAtAddr();
		}
		else
		{
			end = 1;
		}
	}
}
