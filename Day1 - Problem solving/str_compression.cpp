#include"str_compression.h"

void compress(char* str)
{
	int slow = 0, fast = 1, count = 1;
	for (; str[fast]; fast++)
	{
		if (str[fast] == str[fast - 1])
			count++;
		else
		{
			str[slow++] = str[fast - 1];
			if (count > 1) str[slow++] = '0' + count;
			count = 1;
		}
	}
	str[slow++] = str[fast - 1];
	if (count > 1) str[slow++] = '0' + count;
	str[slow] = '\0';
	//*str = (char*) realloc(*str, slow);  //we need to use a double pointer if we want to realloc
}

void test_str_compression()
{
	char* str = (char*)malloc(100);
	printf("Enter a string to be compressed\t");
	scanf_s("%s", str, 100);
	compress(str);
	printf("%s", str);
}