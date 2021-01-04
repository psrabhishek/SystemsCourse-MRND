#include"MergeSort_dll.h"

Dnode* merge_sort_dll(Dnode* head)
{
	if (!head || !head->next)  // return if there are less than 2 nodes
		return head;

	Dnode *head1 = head, *head2 = head; //head2->slow ptr, head1->fast ptr
	while (head2->next && head1->next && head1->next->next) // finding mid-point
	{
		head2 = head2->next;
		head1 = head1->next->next;
	}
	head1 = head2->prev;
	if (head1)
		head1->next = NULL;
	head2->prev = NULL;
	head1 = head;

	merge_sort_dll(head1);
	merge_sort_dll(head2);
	return merge_dll(head1, head2);
}

Dnode* merge_dll(Dnode* head1, Dnode* head2)
{
	if (!head1) return head2;
	if (!head2) return head1; //if either DLL is null return the other DLL

	Dnode* res = NULL, *res_temp = NULL;

	//initial iteration
	if (head1->data < head2->data)
	{
		res_temp = head1;
		head1->prev = NULL;
		head1 = head1->next;
		res_temp->next = NULL;
	}
	else
	{
		res_temp = head2;
		head2->prev = NULL;
		head2 = head2->next;
		res_temp->next = NULL;
	}
	res = res_temp;

	//next iterations
	while (head1 && head2)
	{
		if (head1->data < head2->data)
		{
			res_temp->next = head1;
			head1->prev = res_temp;
			head1 = head1->next;
			res_temp = res_temp->next;
			res_temp->next = NULL;
		}
		else
		{
			res_temp->next = head2;
			head2->prev = res_temp;
			head2 = head2->next;
			res_temp = res_temp->next;
			res_temp->next = NULL;
		}
	}
	while (head1)
	{
		res_temp->next = head1;
		head1->prev = res_temp;
		head1 = head1->next;
		res_temp = res_temp->next;
		res_temp->next = NULL;
	}
	while (head1)
	{
		res_temp->next = head2;
		head2->prev = res_temp;
		head2 = head2->next;
		res_temp = res_temp->next;
		res_temp->next = NULL;
	}
	return res;
}

void test_merge_sort_dll()
{
	int size, iter, temp_data;
	Dnode*head = NULL, *temp = NULL;

	printf("\nEnter no of elements\t");
	scanf_s("%d", &size);
	printf("Enter the DLL elements\n");
	for (iter = 0; iter < size; iter++)
	{
		scanf_s("%d", &temp_data);
		temp = create_dnode(temp_data);
		temp->next = head;
		if (head) head->prev = temp;
		head = temp;
	}
	head = merge_sort_dll(head);
	while (head)
	{
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}