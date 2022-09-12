/*vulp.c*/
//a vulnerable logging program

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char* fn = "logfile";
	char buffer[60] = {0};
	FILE* fp;
	int i = 0;
	int a = 0;

	printf("This is a simple logging program.\n");
	printf("Provide an input to be logged to %s:\n", fn);

	//get user input
	scanf("%50s", buffer);

	printf("\nInput received. Checking to ensure you have access to %s...\n", fn);

	if (!access(fn, W_OK))
	{
		printf("Permissions check passed...\n");

		//open the file for append
		fp = fopen(fn, "a+");
		fwrite("\n", sizeof(char), 1, fp);
		fwrite(buffer, sizeof(char), strlen(buffer), fp);
		fclose(fp);
	}
	else printf("No permission \n");
}
