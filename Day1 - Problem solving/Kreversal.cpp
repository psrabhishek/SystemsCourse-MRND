#include"Kreversal.h"
Node* input()
{
	int size;
	printf("size: ");
	scanf_s("%d", &size);
	printf("enter the numbers\n");
	Node *head = NULL, *tempo=NULL;
	int  num;
	for (int ind = 0; ind < size;ind++)
	{
		Node* temp = (Node*)malloc(sizeof(Node));
		scanf_s("%d", &num);
		temp->data = num;
		temp->next = NULL;
		if (head == NULL)
		{
			tempo = head = temp;
		}
		else
		{
			tempo->next = temp;
			tempo = temp;
		}
	}
	return head;
}
Node* reverse(Node *head, int k)
{
	int count = 0;
	Node * temp = head;
	temp = head;
	while (temp && count < k)
	{
		temp = temp->next;
		count++;
	}
	if (count == k)
	{
		Node* cur = head;
		Node *prev = NULL, *nex=NULL;
		count = 0;
		while (cur && count < k)
		{
			count++;
			nex = cur->next;
			cur->next = prev;
			prev = cur;
			cur = nex;
		}
		if (nex != NULL)
		{
			head->next = reverse(nex, k);
		}
		return prev;
	}
	return head;
}
void reverseLLK()
{
	Node *head = input();
	Node* temp = head;
	printf("enter the k value: ");
	int k,count=0;
	scanf_s("%d", &k);
	head=reverse(head, k);
	temp = head;
	while (temp)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
}