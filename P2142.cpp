#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e4 + 10;

int n[maxn],  m[maxn], an[maxn];
char s[maxn], k[maxn];
bool pd;

int main() {
	ios::sync_with_stdio(false);
	cin >> s >> k;
	int a = strlen(s);
	int b = strlen(k);
	int maxl = max(a, b);
//	cout << a << endl << b << endl;
	if (a < b || (a == b && s[0] - '0' < k[0] - '0')) {
		swap(s, k);
		pd = 1;
	}
	a = strlen(s);
	b = strlen(k);
	for (int i = a; i > 0; i--) {
		n[i] = s[a - i] - '0';
	}
	for (int i = b; i > 0; i--) {
		m[i] = k[b - i] - '0';
	}
	for (int i = 1; i <= maxl; i++) {
		if (n[i] < m[i]) {
			n[i + 1]--;
			n[i] += 10;
		}
		an[i] = n[i] - m[i];
	}
	while(an[maxl] == 0) maxl--;
//	cout << maxl << endl; 
	if (maxl < 1) cout << "0";
	if (pd) cout << "-";
	for (int i = maxl; i > 0; i--) cout << an[i];
	
	return 0;
}
