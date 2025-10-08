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
	printf("正向输出：");
	for (node *p = head; p; p = p->next) {
		printf("%d ", p->val);
	}
	printf("\n");
	
	if(!head) return;
	printf("反向输出：");
	node *p = head;
	while(p->next) p = p->next ;
	for (; p; p = p -> prev) printf("%d ", p->val);
	printf("\n");
} 

//按值查找节点 
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
	//注意，这两步顺序不能乱！！！ 
	if (tmp->next) {
		tmp->next->prev = nw;
	}
	tmp->next = nw;
	//改变了4个指针，将插入的前后指针更改，更改前一个的后指针，若插入的不是最后一位，还需要更改后一位节点的前指针 
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
	if (tar->prev) tar->prev->next = tar->next; // 如果删掉的节点有上一位节点，那么改变上一位节点的next 指针至目标节点的下一个next 
	else *head = tar->next; //更新头节点 
	if (tar->next) tar->next->prev =  tar->prev;
	//如果不是末尾节点，那么就要更新下一个节点的prev指针到目标节点的prev 
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
	
	printf("\n在val = 2后插入99：\n");
	node *tmp = find_node(head, 2);
	insert_back(tmp, 99);
	print1(head);
	
	printf("\n修改val = 3的节点为100\n");
	node *p = find_node(head,  3);
	geng(p, 100);
	print1(head);
	
	printf("\n在val= 5前插入60\n");
	insert_front(find_node(head, 5), 60);
	print1(head);
	
	printf("\n删除val = 0的节点（头节点）：\n");
	del(&head, find_node(head, 0));
	print1(head);
	
	freenode(head);
	return 0;
}
