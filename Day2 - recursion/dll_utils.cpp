#include"dll_utils.h"

Dnode* create_dnode(int data)
{
	Dnode* temp = (Dnode*)malloc(sizeof(Dnode));
	temp->data = data;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}