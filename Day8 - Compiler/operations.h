#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include"tables.h"




void data(char* op1, int* addr_var, int* start_byte, struct symbol_table* st);
void cons(char* op1, int* addr_var, int* start_byte, int* memory, struct symbol_table* st);

void mov(char* op1, char* op2, int* addr_var, struct intermediate_table* it);

void add(char* op1, char* op2, char* op3, struct intermediate_table* it);
void sub(char* op1, char* op2, char* op3, struct intermediate_table* it);
void mul(char* op1, char* op2, char* op3, struct intermediate_table* it);


void process_jump(char* op1, struct intermediate_table* it);
void process_if(char* op1, char* op2, char* op3, struct intermediate_table* it, int* stack, int* top, int inst_no);
void process_else(struct intermediate_table* it_head, intermediate_table* it, int* stack, int* top, int inst_no);
void process_endif(struct intermediate_table* it_head, int*stack, int* top, int inst_no);


void print(char* op1, int* addr_var, struct intermediate_table* it);
void read(char* op1, struct intermediate_table* it);