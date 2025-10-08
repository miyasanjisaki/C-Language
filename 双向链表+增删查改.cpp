#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
	struct node *prev;
}node;

node *create_node(int x) {
	node *p = (node *) malloc(sizeof(node));
	p->val =  x;
	p->prev = NULL;
	p->next = NULL;
	return p;
} 

node *init_list(int n) {
	if (n <= 0) return NULL;
	node *head = create_node(0);
	node *tmp = head;
	for (int i = 1; i < n; i++) {
		node *p = create_node(i);
		tmp->next = p;
		p->prev = tmp; 
		tmp = p;
	}
	return head;
}

void print1(node *head) {
	printf("���������");
	for (node *p = head; p; p = p->next) {
		printf("%d ", p->val);
	}
	printf("\n");
	
	if(!head) return;
	printf("���������");
	node *p = head;
	while(p->next) p = p->next ;
	for (; p; p = p -> prev) printf("%d ", p->val);
	printf("\n");
} 

//��ֵ���ҽڵ� 
node *find_node(node *head, int val) {
	for (node *p = head; p; p = p->next) {
		if (p->val == val) return p;
	}
	return NULL;
}

void insert_back(node *tmp, int val) {
	if (!tmp) return ;
	node *nw = create_node(val);
	nw->next = tmp->next;
	nw->prev = tmp;
	//ע�⣬������˳�����ң����� 
	if (tmp->next) {
		tmp->next->prev = nw;
	}
	tmp->next = nw;
	//�ı���4��ָ�룬�������ǰ��ָ����ģ�����ǰһ���ĺ�ָ�룬������Ĳ������һλ������Ҫ���ĺ�һλ�ڵ��ǰָ�� 
}

void insert_front(node *tmp, int val) {
	if (!tmp) return;
	node *nw = create_node(val);
	nw->next = tmp;
	nw->prev = tmp->prev;
	if (tmp->prev) {
		tmp->prev->next = nw;
	}
	tmp->prev = nw;
} 

void del(node **head, node *tar) {
	if (!tar || (!*head)) return;
	if (tar->prev) tar->prev->next = tar->next; // ���ɾ���Ľڵ�����һλ�ڵ㣬��ô�ı���һλ�ڵ��next ָ����Ŀ��ڵ����һ��next 
	else *head = tar->next; //����ͷ�ڵ� 
	if (tar->next) tar->next->prev =  tar->prev;
	//�������ĩβ�ڵ㣬��ô��Ҫ������һ���ڵ��prevָ�뵽Ŀ��ڵ��prev 
	free(tar);
}

void geng(node *tar, int nval) {
	if (tar) tar->val = nval;
} 

void freenode(node *head) {
	while (head) {
		node *tmp = head;
		head = head->next;
		free(tmp);
	}
}

int main() {
	node *head = init_list(13);
	print1(head); 
	
	printf("\n��val = 2�����99��\n");
	node *tmp = find_node(head, 2);
	insert_back(tmp, 99);
	print1(head);
	
	printf("\n�޸�val = 3�Ľڵ�Ϊ100\n");
	node *p = find_node(head,  3);
	geng(p, 100);
	print1(head);
	
	printf("\n��val= 5ǰ����60\n");
	insert_front(find_node(head, 5), 60);
	print1(head);
	
	printf("\nɾ��val = 0�Ľڵ㣨ͷ�ڵ㣩��\n");
	del(&head, find_node(head, 0));
	print1(head);
	
	freenode(head);
	return 0;
}
