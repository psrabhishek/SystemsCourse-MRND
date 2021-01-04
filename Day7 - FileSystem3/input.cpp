#include"input.h"

void start()
{
	char buff[100 * bytesInBlock];
	char command[10], file_name[100], new_file_name[100];
	int i;
	while (true)
	{
		if(read_block(0, buff))
			set_meta(buff);
		printf("> ");

		fflush(stdin);
		scanf("%s", &command);
		for (i = 0; command[i]; i++)
			command[i] = tolower(command[i]);
		
		if( !strcmp(get_hdd_path(),"") && strcmp(command, "mount") && strcmp(command, "exit"))
		{
			printf("A Disk must be mounted before executing any other operation\n");
			continue;
		}

		if (!strcmp(command, "format"))
		{
			meta.magic = 98989898;
			for (i = 0; i < meta.no_blocks; i++)
				meta.block_available[i] = 0;
			meta.no_of_files = 0;
			memcpy(buff, &meta, sizeof(meta));
			write_block(0, buff);
		}

		else if (!strcmp(command, "store"))
		{
			scanf("%s%s", &file_name, &new_file_name);
			store(file_name, new_file_name, buff);
		}

		else if (!strcmp(command, "get"))
		{
			scanf("%s%s", &file_name, &new_file_name);
			retrieve(file_name, new_file_name, buff);
		}

		else if (!strcmp(command, "del"))
		{
			scanf("%s", &file_name);
			del(file_name, buff);
		}

		else if (!strcmp(command, "ls"))
		{
			list();
		}

		else if (!strcmp(command, "debug"))
		{
			debug();
		}

		else if (!strcmp(command, "exit"))
		{
			break;
		}
		
		else if (!strcmp(command, "mount"))
		{
			scanf("%s %d", &file_name, &i);
			if( i < minBlockSize || i > maxBlockSize)
			{
				printf("Block size should be between %d and %d\n", minBlockSize, maxBlockSize);
				continue;
			}
			init(file_name, i);
		}
		
		else if (!strcmp(command, "unmount"))
		{
			unmount();
		}

		else
		{
			printf("no command \"%s\" found\n", command);
		}

	}
}
