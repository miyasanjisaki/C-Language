#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

int n, m;
char p[maxn], t[maxn];
int nx[maxn];

void build(char *s, int *p) {
	int j = 0;
	p[0] = 0;
	for (int i = 1; i < m; i++) {
		while(j > 0 && s[i] != s[j]) j = p[i - 1];
		if (s[i] == s[j]) j++;
		p[i] = j;
	}
	
}

int kmp(char *t, char *p) {
	int j = 0;
	build(p, nx);
	for (int i = 0; i < n; i++) {
		while(j > 0 && t[i] != p[j]) j = nx[j - 1];
		if (t[i] == p[j]) j++;
		if (j == m) {
			printf("%d", i - j + 1);
			j = nx[j - 1];
		}
	} 
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t >> p;
	n = strlen(t);
	m = strlen(p);
	kmp(t, p);
	return 0;
}
