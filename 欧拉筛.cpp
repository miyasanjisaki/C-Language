#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 10;

int n, cnt, prime[maxn];
bool flag[maxn] = {};

void gdbh(int n) {
	for (int i = 2; i <= n; i++) {
		if (!flag[i]) {
			cnt++;
			prime[cnt] = i;
//			cout << i << endl;
		}
		for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	gdbh(200000);
	flag[0] = 1;
	for (int i = 2; i <= n; i++) {
		int b = n;
		if (!flag[i]) {
			b -= i;
			for (int j = 2; j <= b; j++) {
				if ((!flag[j]) && (!flag[b - j])) {
					cout << i << " " << j << " " << b - j << endl;
					return 0;
				}
			}
		}
	}
	return 0;
}
