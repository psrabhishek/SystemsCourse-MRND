#include"disk_io.h"

unsigned int get_file_size(char* file_name)
{
	FILE* fp = fopen(file_name, "rb");
	fseek(fp, 0, SEEK_END);
	unsigned int size = ftell(fp);
	fclose(fp);
	return size;
}

void write_block(int block, void* buff)
{
	FILE* fp = fopen(hdd_file, "rb+");
	fseek(fp, block * blockSize * bytesInBlock, SEEK_SET);
	fwrite(buff, 1, blockSize * bytesInBlock, fp);
	fclose(fp);
}

int read_block(int block, void* buff)
{
	FILE* fp = fopen(hdd_file, "rb+");
	if (!fp)
	{
		printf("Please mount proper disk\n");
		return 0;
	}
	fseek(fp, block * blockSize * bytesInBlock, SEEK_SET);
	fread(buff, 1, blockSize * bytesInBlock, fp);
	fclose(fp);
	return 1;
}

int read_meta(void* buff, int size)
{
	FILE* fp = fopen(hdd_file, "rb+");
	if (!fp)
	{
		printf("Please mount proper disk\n");
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	fread(buff, 1, size, fp);
	fclose(fp);
	return 1;
}

void init(char* file_name, int block_size)
{
	strcpy(hdd_file, file_name);
	FILE* fp = fopen(hdd_file, "rb+");
	if (!fp)
	{
		printf("Disk \"%s\" not found\n", hdd_file);
		strcpy(hdd_file, "");
	}
	else
	{
		printf("Disk \"%s\" Mounted Succesfully\n", hdd_file);
		blockSize = block_size;
	}
	fclose(fp);
}

int get_block_size()
{
	return blockSize ;
}

char* get_hdd_path()
{
	return hdd_file;
}

void unmount()
{
	strcpy(hdd_file, "");
	printf("Un-Mounted Succesfully\n");
}
