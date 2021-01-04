#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include"disk_io.h"
#include<string.h>

struct file{
	char file_name[20];
	unsigned int starting_block, no_of_blocks, file_length;
};

typedef struct file File;

struct meta{
	int magic;
	int available_blocks;
	File files[32];
	int no_of_files;
	bool block_available[6400];
};

typedef struct meta Meta;

unsigned int get_file_size(char* file_name);

void store(Meta* meta, char* filename, char* new_file_name, char*buff);

void retrieve(Meta* meta, char* filename, char* new_file_name, char*buff);

void del(Meta* meta, char* filename, char*buff);

void list(Meta* meta);

void debug(Meta* meta);