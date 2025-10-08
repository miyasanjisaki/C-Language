#include <stdio.h>
#include <string.h>
#define maxn 100005 + 10

int BF(char T[], char P[]) {
    int n = strlen(T);
    int m = strlen(P);
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while(j < m && T[i + j] == P[j]) j++;
        if (j == m) return i;
    }
    return -1;
}

int main() {
    char T[105], P[105];
    scanf("%s", T);
    scanf("%s", P);
    int ans = BF(T, P);
    if (ans != -1) printf("%dweipipei!\n", ans);
    else printf("NO answer!\n");
}
