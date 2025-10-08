#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 10;

char p[maxn], t[maxn];
int nx[maxn];
int n, m;

void build(char *s, int *p) {
	int j = 0; 
	p[0] = 0;
	for (int i = 1; i < m; i++) {
		while(j > 0 && s[i] != s[j]) j = p[i - 1];
		if (s[i] == s[j]) j++;
		p[i] = j;
	}
}

void kmp(char *t, char *p) {
	build(p, nx);
	int j = 0;
	for (int i = 0; i < n; i++) {
		while (j > 0 && t[i] != p[j]) j = nx[j - 1];
		if (t[i] == p[j]) j++;
		if (j == m) {
			printf("%d\n", i - m + 2);
			j = nx[j - 1];
		}
	}
	for (int i = 0; i < m; i++) {
//		cout << nx[i] << " ";
		printf("%d ", nx[i]);
	}
}

int main() {
	scanf("%s%s", t, p);
	n = strlen(t);
	m = strlen(p);
	kmp(t, p);
	return 0;
} 
