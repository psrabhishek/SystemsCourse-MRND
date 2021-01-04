#include"ll_utils.h"


Node* create_node(int num)
{
	Node* temp = (Node*)malloc(sizeof(*temp));
	temp->data = num;
	temp->next = NULL;
	return temp;
}

Node* int_to_ll(int num)
{
	int count = 0;
	Node* head = NULL, *temp;
	while (num)
	{
		temp = create_node(num % 10);
		temp->next = head;
		head = temp;
		num /= 10;
	}
	return head;
}