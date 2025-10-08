#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e7 + 10;

int n, cnt;
bool flag[maxn];
int prime[maxn];
//bool prime(int n) {
//	for (int i = 2; i < n; i++) {
//		if (n % i == 0) {
//			return 0;
//		} 
//	}
//	return 1;
//}

int main() {
	memset(flag, 0, sizeof(flag));
	cin >> n;
//	prime[1] = 2;
	cnt = 1;
	for (int i = 2; i <= n; i++) {
		if (!flag[i]) {
			prime[cnt] == i;
//			cout << i << endl;
			cnt++;
			for (int j = 2; j <= n / i; j++) {
				flag[i * j] = 1;
			}
		}
	}
	cout << "质数个数：" << cnt - 1;

//	for (int i = 2; i < n; i++) {
//		if (prime(i)) {
////			cout << i << endl;
//			cnt++;
//		}	
//	}
//	cout << cnt << endl;
//	if (prime(n)) {
//		cout << "Yes" << endl;
//	} else {
//		cout << "No" << endl;
//	}
//	for (int i = 2; i < n; i++) {
//		if (n % i == 0) {
//			cout << "No" << endl;
//			cnt++;
//			break;
//		}
//	}
//	if (!cnt) {
//		cout << "Yes" << endl;
//	}
	return 0;
}
 
