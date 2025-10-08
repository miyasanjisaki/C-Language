#include <stdio.h>


int a1[105] = {};
int a2[] = {1, 2, 3, 4, 55, 6, 7, 10};
int a3[4] = {1, 2};
int c[14] = {[3] =  4, [2] = 10, [12] = 7};

int main() {
	for (int i = 1;  i <= 100; i++) printf("%d ", a1[i]); 
	int k = sizeof(a2) / sizeof (a2[0]);
	printf("\n");
	for (int i = 0; i < k; i++)  cout << a2[i] << " ";
	cout << endl;
	for (int i = 0; i < 4; i++) cout << a3[i] << " ";
	cout << endl;
	for (int i = 0; i < 14; i++) cout << c[i] << " ";
	cout << endl;
	
	return 0;
}
