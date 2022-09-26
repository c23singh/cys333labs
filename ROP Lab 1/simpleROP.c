//2022 UPDATE - this comment is incorrect!!!
// compile with gcc simpleROP.c -o simpleROP -Wl,-z,relro -fno-stack-protector -O3
// the last part is linker flags for making this program relocatable/readonly

//2022 UPDATE - use gcc simpleROP.c -o simpleROP -Wl,-z,relro -fno-stack-protector -no-pie -O1
// -no-pie is required to keep the .text segment at a static location
// -O1 is required as -O3 causes breakpoints to not work while -O2 causes difficulties with properly exploiting
// NOTE: does NOT 16-byte stack align

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

void readLogfile(int isAdmin)
{
	if (isAdmin == 0)
	{
		printf("Only the admin can read the logfile!\n");
	}
	else
	{
		int c;
		FILE *file;
		file = fopen("logfile", "r");
		if (file) {
  			while ((c = getc(file)) != EOF)
	    		putchar(c);
	    	}
		fclose(file);
	}
}

void writeLogfile()
{

	int bufferSize = 256;
	char buf[sizeof(bufferSize)];		// hmm
	int inputCount = 0;
	int result = 0;

	printf("Enter your note up to 255 chars\n");

	result = scanf("%s",buf);

	if (result <= 0)
	{
		puts("input error\n");
	}
	FILE *fp = fopen("logfile", "a+");
	if (fp == NULL)
	{
		puts("Error opening logfile\n");
	}
	else
	{
		fputs(buf, fp);
		fputs("\n", fp);
	}

	fclose(fp);
}


void main() {
	int end = 0;
	int input = 0;
	int result = 0;

	// checks to see if user is an admin (real uid 0)
	int isAdmin = 0;
	uid_t test = getuid();

	if (test == 0)
	{
		isAdmin = 1;
	}

	while(end == 0)
	{
		int inputCount = 0;

		printf("\n************************************************\n");
		printf("DoStuff is a program which lets a user do stuff.\n");
		printf("What would you like to do?\n");
		printf("1. Write to logfile\n");
		printf("2. Read the logfile\n");
		printf("3. Exit\n");
		printf("************************************************\n");

		result = scanf("%d", &input);

		if (result == 0 || result == EOF || input <= 0 || input > 3)
		{
			while (fgetc(stdin) != '\n');	//get rid of garbage
			printf("Bad input, try again\n");
		}
		else if (input == 1)
		{
			writeLogfile();
		}
		else if (input == 2)
		{
			readLogfile(isAdmin);
		}
		else
		{
			end = 1;
		}
	}
}
