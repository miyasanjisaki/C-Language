#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxn 105 + 10

void inti(void) {
	srand((unsigned) time(NULL));
} 
int nw(void) {
	return rand() % maxn + 1;
}

void gus(int ass) {
	int gs, num = 0;
	for (;;) {
		num++;
		printf("guess a Number!\n");
		scanf("%d", &gs);
		if (gs == ass) {
			printf("You are right!\n");
			return;
		} else if (gs > ass) {
			printf("Oh no,that's so big!\n");
		} else {
			printf("Oh please, that's too small!\n");
		}
	}
}

int main(void) {
	char com;
	int sc;
	printf("������Ϸ�� ������\n");
	printf("����Y����y:");
	scanf("%c", &com);
	inti();
	do {
		sc = nw();
		printf("�ٺٺ٣���ѡ����");
		gus(sc);
		printf("����һ�Σ�(Y / N)");
		scanf(" %c", &com);
		printf("\n");
	} while(com == 'Y' || com == 'y');
	return 0;
}
