#include"operations.h"

void data(char* op1, int* addr_var, int* start_byte, struct symbol_table* st)
{
	char var, junk, i = 0;
	for (i = 0; op1[i]; i++)
		if (op1[i] != ' ') break;
	var = toupper(op1[i]);
	addr_var[var - 'A'] = *start_byte;
	int size = 1;
	
	for (i = 0; op1[i]; i++)
		if (op1[i] == '[')
			break;
	if (op1[i])
		sscanf(op1 + i + 1, "%d", &size);
	printf("{%c} %d\n", var, *start_byte);
	
	st->name[0] = var; 
	st->name[1] = '\0';
	st->address = *start_byte;
	st->size = size;

	*start_byte += size;
}

void cons(char* op1, int* addr_var, int* start_byte, int* memory, struct symbol_table* st)
{
	char var, junk;
	int size = 1, i = 0, value;

	for (i = 0; op1[i]; i++)
		if (op1[i] != ' ') break;

	var = toupper(op1[i]);
	sscanf(op1 + i + 1, "%d", &value);
	printf("%c %d\n", op1[i], *start_byte);
	addr_var[var - 'A'] = *start_byte;

	st->name[0] = var;
	st->name[1] = '\0';
	st->address = *start_byte;
	st->size = size;

	*start_byte += size;

	*(memory + *start_byte) = value;
}

void mov(char* op1, char* op2, int* addr_var, struct intermediate_table* it)
{
	int i = 0, j = 0;
	for (i = 0; op1[i]; i++)
		if (op1[i] != ' ') break;
	for (j = 0; op2[j]; j++)
		if (op2[j] != ' ') break;

	if (strlen(op1) == 2)
	{
		printf("02, %02d, %04d\n", op1[0] - 'A', addr_var[op2[0]-'A']);
		it->op = 2;
		it->p1 = op1[0] - 'A';
		it->p2 = addr_var[op2[0] - 'A'];
	}
	else
	{
		printf("01, %04d, %02d\n", addr_var[op1[0]-'A'], op2[0] - 'A');
		it->op = 1;
		it->p1 = addr_var[op1[0] - 'A'];
		it->p2 = op2[0] - 'A';
	}
}

void add(char* op1, char* op2, char* op3, struct intermediate_table* it)
{
	printf("3 %02d, %02d, %02d\n", op1[0] - 'A', op2[0] - 'A', op3[0] - 'A');
	it->op = 3;
	it->p1 = op1[0] - 'A';
	it->p2 = op2[0] - 'A';
	it->p3 = op3[0] - 'A';
}

void sub(char* op1, char* op2, char* op3, struct intermediate_table* it)
{
	printf("4 %02d, %02d, %02d\n", op1[0] - 'A', op2[0] - 'A', op3[0] - 'A');
	it->op = 4;
	it->p1 = op1[0] - 'A';
	it->p2 = op2[0] - 'A';
	it->p3 = op3[0] - 'A';
}

void mul(char* op1, char* op2, char* op3, struct intermediate_table* it)
{
	printf("5 %02d, %02d, %20d\n", op1[0] - 'A', op2[0] - 'A', op3[0] - 'A');
	it->op = 5;
	it->p1 = op1[0] - 'A';
	it->p2 = op2[0] - 'A';
	it->p3 = op3[0] - 'A';
}

void process_jump(char* op1, struct intermediate_table* it)
{
	printf( "6 %s\n", op1);
	it->op = 6;
	it->p1 = op1[0] - 'A';// gottta change this!!
}


void process_if(char* op1, char* op2, char* op3, struct intermediate_table* it, int* stack, int* top, int inst_no)
{
	printf("7 %d\n", op1[0] - 'A');
	int op;
	if (!strcmp(op2, "EQ"))
	{
		op = 8;
	}

	else if (!strcmp(op2, "LT"))
	{
		op = 9;
	}

	else if (!strcmp(op2, "gt"))
	{
		op = 10;
	}

	else if (!strcmp(op2, "lteq"))
	{
		op = 11;
	}
	else if (!strcmp(op2, "gteq"))
	{
		op = 12;
	}
	it->op = 7;
	it->p1 = op1[0] - 'A';
	it->p2 = op3[0] - 'A';
	it->p3 = op;
	stack[++*top] = inst_no;
}

void process_else(struct intermediate_table* it_head, struct intermediate_table* it, int* stack, int *top, int inst_no)
{
	int prev_inst = stack[*top--], i;
	for (i = 1; i < prev_inst; i++)
		it_head = it_head->next;
	it_head->p4 = inst_no + 1;
	stack[++*top] = inst_no;
	it->op = 6;
}

void process_endif(struct intermediate_table* it_head, int* stack, int *top, int inst_no)
{
	int prev_inst = stack[*top--], i;
	for (i = 1; i < prev_inst; i++)
		it_head = it_head->next;
	it_head->p1 = inst_no;
}

void print(char* op1, int* addr_var, struct intermediate_table* it)
{
	int i, size;
	it->op = 13;
	switch (strlen(op1))
	{
	case 1:
		it->p1 = addr_var[op1[0] - 'A'];
		printf("13 %d\n", addr_var[op1[0] - 'A']);
		break;
	case 2:
		printf("13 %d\n", op1[0] - 'A');
		it->p1 = op1[0] - 'A';
		break;
	default:
		for (i = 0; op1[i]; i++)
			if (op1[i] >= '0' && op1[i] <= '9') break;
		sscanf(op1 + i, "%d", &size);
		printf("13 %d\n", addr_var[op1[0] - 'A'] + size * 4);
		it->p1 = addr_var[op1[0] - 'A'] + size * 4;
	}
}

void read(char* op1, intermediate_table* it)
{
	int i;
	for (i = 0; op1[i]; i++)
		if (op1[i] != ' ') break;

	printf("14, %02d\n", op1[i] - 'A');
	it->op = 14;
	it->p1 = op1[i] - 'A';
}

