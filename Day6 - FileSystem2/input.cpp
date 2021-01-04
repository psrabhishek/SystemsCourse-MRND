#include"input.h"

void start()
{
	Meta *meta = (Meta*)calloc(1, sizeof(Meta));
	char buff[16 * 1024];

	char command[10], file_name[20], new_file_name[20];
	int i;
	while (true)
	{
		read_block(0, buff);
		memcpy(meta, buff, sizeof(Meta));
		printf("> ");

		scanf("%s", &command);
		for (i = 0; command[i]; i++)
			command[i] = tolower(command[i]);

		if (!strcmp(command, "format"))
		{
			meta = (Meta*)calloc(1, sizeof(Meta));
			meta->magic = 98989898;
			meta->available_blocks = 6399;
			memcpy(buff, meta, sizeof(Meta));
			write_block(0, buff);
		}

		else if (!strcmp(command, "store"))
		{
			scanf("%s%s", file_name, new_file_name);
			store(meta, file_name, new_file_name, buff);
		}

		else if (!strcmp(command, "get"))
		{
			scanf("%s%s", file_name, new_file_name);
			//printf("%s %s\n", file_name, new_file_name);
			retrieve(meta, file_name, new_file_name, buff);
			
		}

		else if (!strcmp(command, "del"))
		{
			scanf("%s", file_name);
			del(meta, file_name, buff);
		}

		else if (!strcmp(command, "ls"))
		{
			list(meta);
		}

		else if (!strcmp(command, "debug"))
		{
			debug(meta);
		}

		else if (!strcmp(command, "exit"))
		{
			break;
		}

		else
		{
			printf("no command \"%s\" found\n", command);
		}

	}
}