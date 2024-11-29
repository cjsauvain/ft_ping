#include "ft_ping.h"

t_command	get_option(t_command command, char *argument)
{
	int	i = 1;

	while (argument[i])
	{
		if ((argument[i] != 'v' && argument[i] != '?') || argument[0] != '-')
		{
			fprintf(stderr, "ping: invalid option -- '%c'\n", argument[i]);
			fprintf(stderr, "Try 'ping --help' or 'ping --usage' \
					for more information.\n");
			exit(64);
		}
		else
		{
			if (argument[i] == '?')
				command.option[0] = '?';
			else
				command.option[0] = 'v';
			return command;
		}
		i++;
	}
	return command;
}

t_command	parsing(int argc, char **argv)
{
	t_command	command;
	int			i;

	if (argc == 1)
	{
		fprintf(stderr, "ft_ping: missing host operand\n");
		fprintf(stderr, "Try 'ping -?' for more information.\n");
		exit(64);
	}
	//print help:	- if encounter ? without having invalid options placed BEFORE ("-v?" || "-v -?")
	command.option[0] = '0';
	command.option[1] = '\0';
	i = 1;
	while (argv[i])
	{
		if (strchr(argv[i], '-') && (command.option[0] == '0' 
			|| command.option[0] == 'v'))
			command = get_option(command, argv[i]);
		else if (!strchr(argv[i], '-'))
			command.ip_addr = argv[i];
		i++;
	}
	return command;
}
