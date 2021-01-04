#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<string.h>

struct symbol_table{
	char name[8];
	int address, size;
	struct symbol_table* next;
};


struct intermediate_table{
	int op, p1, p2, p3, p4;
	struct intermediate_table * next;
};

struct label_table
{
	char name[8];
	int address;
	struct label_table* next;
};

struct symbol_table* create_st_node();

struct label_table* create_lt_node();

struct intermediate_table* create_it_node();

void insert_st_node(struct symbol_table* st);

void insert_it_node(struct intermediate_table* it);

void insert_lt_node(struct label_table* lt);