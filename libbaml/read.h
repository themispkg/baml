#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <baml.h>

char *read_entry(int argc, char *argv[]){
	FILE	*fp;
	char	**format;
	int		first_arg;
	char	buffer[3065];
	char	*store;
	char	hopen;
	size_t	stcursor;
	size_t	lfile;

	buffer[3064] = 0;

	if (argc > 1)
	{
		if (!(format = valid_arg(argv[1])))
		{
			printf("Invalid determinator argument.\n");
			return (1);
		}
		if (!strncmp(argv[1], "--", 2))
			first_arg = 2;
		else
			first_arg = 1;
		for (int i = first_arg; i < argc; i++)
		{
			fp = fopen(argv[i], "r");
			store = (char *) calloc(1, sizeof(char));
			hopen = 0;
			lfile = 0;

			if (fp == NULL)
			{
				printf("Cannot open file: %s\n", argv[i]);
				continue ;
			}
			while (fgets(buffer, 3065, fp))
			{
				stcursor = dstr(store, buffer);
				if (store[stcursor - 1] == '\n')
				{
					lfile++;
					if (store[stcursor - 2] == HEADERTOKEN)
					{
						pheader(store, format, &hopen);
					}
					else if ((stcursor = valid_token(store)))
					{
						if(!hopen)
						{
							printf("Incomplete entry at line %ld\n", lfile);
							return (1);
						}
						pentry(&store[stcursor], format, &hopen);
					}
					free(store);
					store = calloc(1, sizeof(char));
				}
			}
			if (hopen)
				return format[3];
			free(store);
			fclose(fp);
		}
	}
	else
		printf("Incomplete arguments.\n");
	return format[3];
}
