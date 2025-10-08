#include <stdio.h>

int i, j, *p, *q;

void abab(int *arr) {
	arr[2] = 30;
}

void *sort(int *arr, int n, int *max_in, int *min_in) {
	*max_in = arr[0];
	*min_in = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > *max_in) {
			*max_in = arr[i];
		} else if (arr[i] < *min_in) {
			*min_in = arr[i];
		}
	}
}

void swap(int *p, int *q) {
	int k;
	k = *p;
	*p = *q;
	*q = k;
}


int main(void) {
	scanf("%d", &i);
	p = &i;
	q = &j; 
	j = *&i;
	j = 205;
	printf("%d %d\n", q, *q);
	int a, b;
	scanf("%d %d", &a, &b);
	swap(&a, &b);
	printf("%d %d\n", a, b);
	q = p;
	*q = *p;
	int aa[] = {1, 2, 3, 33, 4, 5, 6, 66, 7, 8, 8, 1002, 30};
	int maxn, minn, cnt = 0;
	cnt = sizeof(aa) / sizeof(aa[0]);
	sort(aa, cnt, &maxn, &minn);
	printf("%d  %d\n", maxn, minn);
	printf("%d %d\n", q, *q);
	printf("%d %d\n", p, *p);
	*q = 2;
	printf("%d %d\n", q, *q);
	printf("%d %d\n", p, *p);
	*p = 1331;
	printf("%d %d\n", q, *q);
	printf("%d %d", p, *p);
	return 0;
}
