#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"tables.h"
#include"operations.h"

void read_1_operand(char* op1, FILE** fp)
{
	fgets(op1,10, *fp);
}

void read_2_operands(char* op1, char* op2, FILE** fp)
{
	fscanf(*fp, "%s%s", op1, op2);
	int len = strlen(op1);
	if (op1[len - 1] == ',')
		op1[len - 1] = '\0';
}

void read_3_operands(char* op1, char* op2, char* op3, FILE** fp)
{
	fscanf(*fp, "%s%s%s", op1, op2, op3);
	int len = strlen(op1);
	if (op1[len - 1] == ',')
		op1[len - 1] = '\0';

	len = strlen(op2);
	if (op2[len - 1] == ',')
		op2[len - 1] = '\0';
}

int main()
{
	char command[10], op1[10], op2[10], op3[10], var, junk=' ';
	int i, value_var[26], addr_var[26], value_reg[26], start_byte = 0, size = 1;
	int* memory = (int*)malloc(sizeof(int) * 100);

	int stack[20] = {}, top = -1;

	FILE* fp = fopen("input.txt", "r");
	FILE* res = fopen("output.txt", "w");

	struct symbol_table* st = create_st_node(), *temp_st = st;
	struct intermediate_table* it = create_it_node(), *temp_it = it;
	struct label_table* lt = create_lt_node(), *temp_lt = lt;
	int count_st = 0, count_it = 0, count_lt = 0, inst_no = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%s", &command);
		for (i = 0; command[i]; i++)
			command[i] = tolower(command[i]);

		if (!strcmp(command, "data"))
		{
			read_1_operand(op1, &fp);
			data(op1, addr_var, &start_byte, temp_st);
			count_st++;
			temp_st->next = create_st_node();
			temp_st = temp_st->next;
		}

		else if (!strcmp(command, "const"))
		{
			read_1_operand(op1, &fp);
			cons(op1, addr_var, &start_byte, memory, temp_st);
			count_st++;
			temp_st->next = create_st_node();
			temp_st = temp_st->next;
		}

		else if (!strcmp(command, "start:"))
		{
			continue;
		}

		else if (!strcmp(command, "mov"))
		{
			read_2_operands(op1, op2, &fp);
			mov(op1, op2, addr_var, temp_it);
			count_it++;
			temp_it->next = create_it_node();
			temp_it = temp_it->next;
			inst_no++;

		}

		else if (!strcmp(command, "add"))
		{
			read_3_operands(op1, op2, op3, &fp);
			add(op1, op2, op3, temp_it);
			count_it++;
			temp_it->next = create_it_node();
			temp_it = temp_it->next;
			inst_no++;

		}

		else if (!strcmp(command, "sub"))
		{
			read_3_operands(op1, op2, op3, &fp);
			sub(op1, op2, op3, temp_it);
			count_it++;
			temp_it->next = create_it_node();
			temp_it = temp_it->next;
			inst_no++;

		}

		else if (!strcmp(command, "mul"))
		{
			read_3_operands(op1, op2, op3, &fp);
			mul(op1, op2, op3, temp_it);
			count_it++;
			temp_it->next = create_it_node();
			temp_it = temp_it->next;
			inst_no++;

		}

		else if (!strcmp(command, "jump"))
		{
			read_1_operand(op1, &fp);
			process_jump(op1, temp_it);
			count_it++;
			temp_it->next = create_it_node();
			temp_it = temp_it->next;
			inst_no++;

		}

		else if (!strcmp(command, "if"))
		{
			read_3_operands(op1, op2, op3, &fp);
			process_if(op1, op2, op3, temp_it, stack, &top, inst_no);
			count_it++;
			temp_it->next = create_it_node();
			temp_it = temp_it->next;
			inst_no++;

		}

		else if (!strcmp(command, "else"))
		{
			process_else(it, temp_it, stack, &top, inst_no);
			count_it++;
			temp_it->next = create_it_node();
			temp_it = temp_it->next;
			inst_no++;
		}

		else if (!strcmp(command, "endif"))
		{
			process_endif(it, stack, &top, inst_no);
		}
		
		else if (!strcmp(command, "print"))
		{
			print(op1, addr_var, temp_it);
			count_it++;
			temp_it->next = create_it_node();
			temp_it = temp_it->next;
			inst_no++;

		}
		
		else if (!strcmp(command, "read"))
		{
			read_1_operand(op1, &fp);
			read(op1, temp_it);
			count_it++;
			temp_it->next = create_it_node();
			temp_it = temp_it->next;
			inst_no++;

		}

		else if (command[strlen(command) - 1] == ':')
		{
			command[strlen(command) - 1] = '\0';
			strcpy(temp_lt->name, command);
			temp_lt->address = inst_no;
			temp_lt->next = create_lt_node();
			temp_lt = temp_lt->next;
			inst_no++;
		}

		else if (!strcmp(command, "end"))
		{
			break;
		}

		else
		{
			printf("%s\n", command);
		}
	}
	printf("\n\n");
	fwrite(&count_st, 4, 1, res);
	while (st)
	{
		printf("%s %d %d\n", st->name, st->address, st->size);
		fwrite(st, sizeof(*st), 1, res);
		st = st->next;
	}
	printf("\n\n");
	fwrite(&count_it, 4, 1, res);
	while (it)
	{
		printf("%d %d %d %d\n", it->op, it->p1, it->p2, it->p3, it->p4);
		fwrite(it, sizeof(*it), 1, res);
		it = it->next;
	}
	printf("\n\n");
	fwrite(&count_lt, 4, 1, res);
	while (lt)
	{
		printf("%s %d\n", lt->name, lt->address);
		fwrite(lt, sizeof(*lt), 1, res);
		lt = lt->next;
	}
	fclose(fp);
	fclose(res);
	getchar();
	return 0;
}