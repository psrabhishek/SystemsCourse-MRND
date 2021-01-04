#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node* next;
};
typedef struct node Node;
Node* reverse(Node *head, int k);
Node* input();
void reverseLLK();