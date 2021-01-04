#pragma once
#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node* next;
};

typedef struct node Node;

Node* create_node(int num);

Node* int_to_ll(int num);