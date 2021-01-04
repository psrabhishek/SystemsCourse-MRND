#include"tables.h"

struct symbol_table* create_st_node()
{
	struct symbol_table* temp = (struct symbol_table*)malloc(sizeof(*temp));
	strcpy(temp->name, "");
	temp->address = -1;
	temp->next = NULL;
	temp->size = -1;
	return temp;
}

struct label_table* create_lt_node()
{
	struct label_table* temp = (struct label_table*)malloc(sizeof(*temp));
	strcpy(temp->name, "");
	temp->address = -1;
	temp->next = NULL;
	return temp;
}

struct intermediate_table* create_it_node()
{
	struct intermediate_table* temp = (struct intermediate_table*)malloc(sizeof(*temp));
	temp->op = -1;
	temp->p1 = -1;
	temp->p2 = -1;
	temp->p3 = -1;
	temp->p4 = -1;
	temp->next = NULL;
	return temp;
}

void insert_st_node(struct symbol_table* st)
{
	st->next = create_st_node();
}

void insert_it_node(struct intermediate_table* it)
{
	it->next = create_it_node();
}

void insert_lt_node(struct label_table* lt)
{
	lt->next = create_lt_node();
}