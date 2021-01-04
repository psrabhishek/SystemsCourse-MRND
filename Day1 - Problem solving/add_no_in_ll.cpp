#include"add_no_in_ll.h"

Node* add_ll(Node*h1, Node*h2)
{
	Node *s1 = create_node(h1->data), *s2 = NULL, *t1 = h1->next, *t2 = NULL, *res = NULL, *t = NULL;
	int c = 0, sum;
	while (t1)
	{
		t2 = create_node(t1->data);
		t2->next = s1;
		s1 = t2;
		t1 = t1->next;

	}
	t1 = h2;
	while (t1)
	{
		t2 = create_node(t1->data);
		t2->next = s2;
		s2 = t2;
		t1 = t1->next;
	}
	t1 = s1;
	t2 = s2;
	while (t1 && t2)
	{
		sum = t1->data + t2->data;
		t = create_node((c + sum) % 10);
		t->next = res;
		res = t;
		c = (c + sum) / 10;
		t1 = t1->next;
		t2 = t2->next;
	}
	while (t1)
	{
		sum = t1->data + c;
		t = create_node((c + sum) % 10);
		t->next = res;
		res = t;
		c = (c + sum) / 10;
		t1 = t1->next;
	}
	while (t2)
	{
		sum = t2->data + c;
		t = create_node((c + sum) % 10);
		t->next = res;
		res = t;
		c = (c + sum) / 10;
		t2 = t2->next;
	}
	return res;
}

void test_add_no_in_ll()
{
	int num1, num2;
	Node* head;
	printf("Enter two integers to be added\n");
	scanf_s("%d%d", &num1, &num2);
	printf("The sum of %d and %d is ", num1, num2);
	head = add_ll(int_to_ll(num1), int_to_ll(num2));
	while (head)
	{
		printf("%d", head->data);
		head = head->next;
	}
}