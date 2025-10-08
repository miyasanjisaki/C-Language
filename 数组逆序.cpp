
#include <bits/stdc++.h>
using namespace std;
 
int digits[10] = {2,0,0,1,1,1,2,1};	// 20011121
int len = 8;
int main() {
    for (int i = len - 1; i >= 0; --i) cout << digits[i];
    cout << endl;
}
