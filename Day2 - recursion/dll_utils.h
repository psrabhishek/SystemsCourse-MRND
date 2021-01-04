#pragma once
#include<stdio.h>
#include<stdlib.h>


struct dnode{
	int data;
	struct dnode *next, *prev;
};

typedef struct dnode Dnode;

Dnode* create_dnode(int data);
