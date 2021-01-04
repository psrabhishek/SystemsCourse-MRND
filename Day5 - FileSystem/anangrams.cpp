/*#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct node{
	char data;
	int no;
	char anagram[50][50];
	struct node* next[26];
};

typedef struct node Node;

Node* create_node(char c)
{
	Node* t = (Node*)malloc(sizeof(Node));
	t->data = c;
	t->no = 0;
	for (int i = 0; i < 26; i++)
	{
		t->next[i] = NULL;
	}
	return t;
}

void find(Node* root, char* word)
{
	int i;
	for (i = 0; word[i]; i++)
	{
		if (!root)
		{
			printf("No anagrams exist\n");
			return;
		}
		root = root->next[word[i] - 'a'];
	}
	if (!root || root->no == 0)
	{
		printf("No anagrams exist\n");
		return;
	}
	printf("\nThe anagrams are\n");
	for (i = 0; i < root->no; i++)
		printf("%s\n", root->anagram[i]);
	printf("\n");
}

void pre_process(Node* root)
{
	char ip[30];
	int i, n;
	Node* temp;
	FILE* fp = fopen("prep.txt", "r");
	while (!feof(fp))
	{
		fscanf(fp, "%s", ip);
		fscanf(fp, "%d", &n);
		temp = root;
		for (i = 0; ip[i]; i++)
		{
			if (ip[i] == '-') continue;
			if (!temp->next[ip[i] - 'a'])
				temp->next[ip[i] - 'a'] = create_node(ip[i] - 'a');
			temp = temp->next[ip[i] - 'a'];
		}
		for (i = 0; i < n;i++)
			fscanf(fp, "%s", temp->anagram[i]);
		temp->no = n;
	}
}

int myCompare(const void * a, const void * b) {
	const char pa = *(const char*)a;
	const char pb = *(const char*)b;

	return pa-pb;
}

int main()
{
	Node* root=create_node(' ');
	pre_process(root);
	char word[20];
	while (true)
	{
		printf(">");
		scanf("%s", word);
		if (!strcmp(word, "END"))
			break;
		qsort(word, strlen(word), sizeof(char), myCompare);
		find(root, word);
	}
	return 0;
}*/