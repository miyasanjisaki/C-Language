#include <bits/stdc++.h>

using namespace std;
 
const int maxn = 1e5 + 10;
 
//int n;
//int cnt = 0;

//bool prime(int n) {
//	for (int i = 2; i * i <= n; i++) {
//		if (n % i == 0) {
//			return 0;
//		}
//	}
//	return 1;
//}
//
//int main() {
//	
//	ios::sync_with_stdio(false);
//	cin >> n;
//	for (int i = 2; i <= n; i++) {
//		if (prime(i)) {
//			cnt++;
//		}
//	}
//	cout << cnt << endl;
//	return 0;
//} 

bool flag[maxn];
int prime[maxn], n, cnt;

int main() {
	memset(flag, 0, sizeof(flag));
	cin >> n;
	for (int i = 2; i <= n; i++) {
		if (!flag[i]) {
			cnt++;
			prime[cnt] = i;
//			cout << i << endl;
			for (int j = 2; j <= n / i; j++) {
				flag[i * j] = 1;
			}
		}
	}
	cout << cnt << endl;
	return 0;
}
