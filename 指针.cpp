#include <stdio.h>

int n, i, *p, *q;

int main(void) {
	i = 1005;
	p = &i;
	printf("%d\n", i);
	printf("%d", p);
	return 0;
}
