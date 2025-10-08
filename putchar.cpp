#include <stdio.h>
#include <ctype.h>

char ch;

int main(void) {
	ch = getchar();
	char s;
	s = toupper(ch);
	
	putchar(s);
	printf("\n%c", ch);
	return 0;
} 
