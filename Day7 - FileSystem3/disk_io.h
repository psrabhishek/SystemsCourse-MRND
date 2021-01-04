#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma once

struct file{
	char file_name[20];
	unsigned int starting_block, no_of_blocks, file_length;
};

typedef struct file File;


#define minBlockSize 8
#define maxBlockSize 100
#define maxBlocks 6400
#define maxFiles 32
#define bytesInBlock 1024
#define Meta()\
struct {\
	int magic;\
	int block_size;\
	int start_block;\
	int no_blocks;\
	int empty_blocks;\
	bool block_available[maxBlocks];\
	int no_of_files;\
	File files[maxFiles];\
}\


unsigned int get_file_size(char* file_name);

static char hdd_file[200] = "";
static int fileSize=1, blockSize=1;

void write_block(int block, void* buff);

int read_block(int block, void* buff);
int read_meta(void* buff, int size);

void init(char* file_name, int block_size);
void unmount();

char* get_hdd_path();

int get_block_size();
