#include"ll_loop_detection.h"


int detect_loop( Node *list)
{
	 Node  *slow = list, *fast = list;

	 while (slow && fast && fast->next)
	 {
		 slow = slow->next;
		 fast = fast->next->next;

		 if (slow == fast)
			 return 1;
	 }
	return 0;
}

void test_loop_detection()
{
	Node *head = create_node(50);
	head->next = create_node(20);
	head->next->next = create_node(15);
	head->next->next->next = create_node(4);
	head->next->next->next->next = create_node(10);

	/* Create a loop for testing */
	head->next->next->next->next->next = head->next->next;
	
	int loop_exists = detect_loop(head);
	if (loop_exists)
		printf("Loop Detected, Working properly\n");
	else
		printf("Loop Not Detected, Not Working properly\n");
}