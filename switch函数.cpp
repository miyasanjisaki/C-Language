#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int g;
	cin >> g;
	switch(g) {
		case 1: case 2:
			cout << "G小于3!\n";
			break;
		case 3:
			cout << "G == 3!" << endl;
			break;
		case 4:
			cout << "G是4！" << endl;
			break;
		default:
			cout << "G不是好东西！" << endl;
			break;
	}
	
	return 0;
}
