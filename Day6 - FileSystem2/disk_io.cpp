#include"disk_io.h"

void write_block(int block, void* buff)
{
	FILE* fp = fopen("db.hdd", "rb+");
	fseek(fp, block * 16 * 1024, SEEK_SET);
	fwrite(buff, 1, 16 * 1024, fp);
	fclose(fp);
}

void read_block(int block, void* buff)
{
	FILE* fp = fopen("db.hdd", "rb+");
	fseek(fp, block * 16 * 1024, SEEK_SET);
	fread(buff, 1, 16 * 1024, fp);
	fclose(fp);
}