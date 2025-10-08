#include <bits/stdc++.h>

using namespace std;

void qs(int a[], int l, int r) {
	if (l >= r) return;
	int i = l, j = r;
	int pi = a[l];
	while(i < j) {
		while(i < j && a[j] >= pi) j--;
		if (i < j) a[i++] = a[j];
		while(i < j && a[i] <= pi) i++;
		if (i < j) a[j--] = a[i];
	}
	a[i] = pi;
	qs(a, l, i - 1);
	qs(a, i + 1, r);
}

int main() {
	int n, b[10005];
	cin >> n;
	for (int i = 1; i <=  n; i++) cin >> b[i];
	qs(b, 1, n);
	for (int i = 1; i <= n; i++) cout << b[i] << " ";
	return 0;
}
