#include"file_utils.h"

unsigned int get_file_size(char* file_name)
{
	FILE* fp = fopen(file_name, "rb");
	fseek(fp, 0, SEEK_END);
	unsigned int size = ftell(fp);
	fclose(fp);
	return size;
}

void store(Meta* meta, char* filename, char* new_file_name, char*buff)
{
	int i = 1, j = 0, size = get_file_size(filename), blocks, offset;
	blocks = size / (16 * 1024);
	if (size % (16 * 1024))
		blocks++;
	if (meta->available_blocks < blocks + 1)
	{
		printf("Not enough Memory to store\n");
		return;
	}
	if (blocks > 4096)
	{
		printf("Max limit for file size is %d only", 16 * 1024 * 4096);
		return;
	}
	int buff2[4096];
	while (i < 6400)
	{
		if (!meta->block_available[i])
		{
			meta->available_blocks--;
			meta->files[meta->no_of_files].starting_block = i;
			meta->block_available[i] = 1;
			break;
		}
		i++;
	}
	FILE* fp = fopen(filename, "rb");
	j = 0;
	while (i < 6400 && j + 1 < blocks)
	{
		if (!meta->block_available[i])
		{
				meta->available_blocks--;
				meta->block_available[i] = 1;
				fread(buff, 1, 16 * 1024, fp);
				write_block(i, buff);
				buff2[j++] = i;
		}
		i++;
	}
	
	if (blocks > 1)
	while (i < 6400)
	{
		if (!meta->block_available[i])
		{
			meta->available_blocks--;
			break;
		}
		i++;
	}
	if (blocks == size / (16 * 1024))
		offset = 16 * 1024;
	else
		offset = size % (16 * 1024);
	
	fread(buff, 1, offset, fp);
	write_block(i, buff);
	meta->block_available[j] = 1;

	if (blocks > 1)
	{
		buff2[j++] = i;
		write_block(meta->files[meta->no_of_files].starting_block, buff2);
	}

	meta->files[meta->no_of_files].file_length = size;
	strcpy(meta->files[meta->no_of_files].file_name, new_file_name);
	meta->files[meta->no_of_files].no_of_blocks = blocks;
	meta->no_of_files++;
	memcpy(buff, meta, sizeof(Meta));
	write_block(0, buff);
	fclose(fp);
}

void retrieve(Meta* meta, char* filename, char* new_file_name, char*buff)
{
	int i = 1, size, j = 0, blocks, start;
	//printf("%d\n", meta->no_of_files);
	for (i = 0; i < meta->no_of_files; i++)
	{
		//printf("%s\n", meta->files[i].file_name);
		if (!strcmp(filename, meta->files[i].file_name))
			break;
	}
	if (i >= meta->no_of_files)
	{
		printf("Could't retrieve the give file\n");
		return;
	}
	size = meta->files[i].file_length;
	start = meta->files[i].starting_block;
	blocks = meta->files[i].no_of_blocks;

	int buff2[4096];
	read_block(start, buff2);
	if (blocks <= 1) buff2[0] = start;
	//printf("%s %s\n", filename, new_file_name);
	FILE* fp = fopen(new_file_name, "wb+");
	for (i = 0; i < blocks - 1; i++)
	{
		read_block(buff2[i], buff);
		fwrite(buff, 1, 16 * 1024, fp);
	}
	if (size % (16 * 1024))
	{
		read_block(buff2[i], buff);
		fwrite(buff, 1, size % (16 * 1024), fp);
	}
	else
	{
		read_block(buff2[i], buff);
		fwrite(buff, 1, 16 * 1024, fp);
	}
	fclose(fp);
}

void del(Meta* meta, char* filename, char*buff)
{
	int i, size, j, blocks, start;
	//printf("%d\n", meta->no_of_files);
	for (i = 0; i < meta->no_of_files; i++)
	{
		//printf("%s\n", meta->files[i].file_name);
		if (!strcmp(filename, meta->files[i].file_name))
			break;
	}
	if (i >= meta->no_of_files)
	{
		printf("Could't find/delete the give file\n");
		return;
	}
	start = meta->files[i].starting_block;
	blocks = meta->files[i].no_of_blocks;
	meta->files[i] = meta->files[meta->no_of_files-1];
	meta->no_of_files--;
	meta->available_blocks += blocks;

	int buff2[4096];
	read_block(start, buff2);
	meta->block_available[start] = 0;
	if (blocks > 1)
	{
		for (i = 0; i < blocks; i++)
		{
			meta->block_available[buff2[i]] = 0;
		}
		meta->available_blocks++;
	}
	
	memcpy(buff, meta, sizeof(Meta));
	write_block(0, buff);
}

void list(Meta* meta)
{
	int i, size, j, blocks, start;
	for (i = 0; i < meta->no_of_files; i++)
	{
		printf("%s\n", meta->files[i].file_name);
	}
	if (i == 0)
	{
		printf("No files found\n");
	}
}

void debug(Meta* meta)
{
	printf("Amount of blocks available is %d\n", meta->available_blocks);
}