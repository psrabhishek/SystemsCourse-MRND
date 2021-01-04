#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include"disk_io.h"
#include<string.h>

static Meta() meta;


void store(char* filename, char* new_file_name, char*buff);

void retrieve(char* filename, char* new_file_name, char*buff);

void del(char* filename, char*buff);

void list();

void debug();

void set_meta( char* data);
