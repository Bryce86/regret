#include <stdio.h>
#ifdef WIN32
#include <Windows.h>
#endif
#include <unistd.h>

const char progress[] = "|/-\\";

int main()
{
	for (int i = 0; i < 100; i += 10) {
		printf("Processing: %3d%%\r",i); /* \r returns the caret to the line start */
		fflush(stdout);
		Sleep(1000);
	}
	printf("\n"); /* goes to the next line */
	fflush(stdout);

	printf("Processing: ");
	for (int i = 0; i < 1000; i += 10) {
		//printf("%c\b", progress[(i/10)%sizeof(progress)]); /* \b goes one back */
		printf("%c\b", progress[(i/10)%strlen(progress)]); /* \b goes one back */
		fflush(stdout);
		Sleep(100);
	}
	printf("\n"); /* goes to the next line */
	fflush(stdout);

	return 0;
}
