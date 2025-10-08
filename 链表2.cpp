#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int val;
	struct node *next;
}node;

node *create_node(int val) {
	node *p = (node *) malloc(sizeof(node));
	p -> val = val;
	p -> next = NULL;
	return p;
}

node *init_list(int n) {
	node *head = create_node(0);
	node *tmp = head;
	for (int i = 1; i < n; i++) {
		tmp -> next = create_node(i);
		tmp = tmp -> next;
	}
	return head;
}

void fre(node *head) {
	node *p;
	while(head) {
		p = head;
		free(p);
		head = head -> next;
	}
}

void node_check(node *p) {
	for (node *i = p; i; i = i -> next) {
		printf("%d ", i -> val);
	}
	printf("\n");
}


int main() {
	node *list = init_list(6);
	node_check(list);
	fre(list);
	return 0;
} 
