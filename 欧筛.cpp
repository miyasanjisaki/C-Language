#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

bool flag[maxn] = {};
int cnt;
int prime[maxn];

int main() {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 2; i <= n; i++) {
		if (!flag[i]) {
			cnt++;
			prime[cnt] = i;
		}
		for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	cout << cnt << endl;
	return 0;
}
