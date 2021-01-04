/*

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct student
{
	char name[8];
	int marks;
	int friend_count;
};

int main()
{
	FILE* fp = fopen("binary.txt", "w+");
	/*struct student s, b;
	strcpy(s.name, "pro");
	s.marks = 40;
	s.friend_count = 5;
	fwrite(&s, sizeof(s), 1, fp);*/
/*	int magic[] = { 1920409673, 543519849, 543449442, 1701080931, 1767990304, 3045740 };
	fwrite(magic, 4, sizeof(magic)/4, fp);
	fclose(fp);
	fopen("binary.txt", "r+");
	//fread(&b, sizeof(b), 1, fp);
	//printf("%s\n%d\n%d\n", s.name, s.marks, s.friend_count);
	//printf("%s\n%d\n%d\n", b.name, b.marks, b.friend_count);
	fclose(fp);
	getchar();
	return 0;

}

*/