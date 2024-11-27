#include "ft_ping.h"

t_command	get_option(t_command command, char *argument)
{
	int	i = 1;

	while (argument[i])
	{
		if ((argument[i] != 'v' && argument[i] != '?') || argument[0] != '-')
		{
			command.status = 64;
			fprintf(stderr, "ping: invalid option -- '%c'\nTry 'ping --help' or 'ping --usage' for more information.", argument[i]);
			return (command);
		}
		else
		{
			if (argument[i] == '?')
				command.option[0] = '?';
			else
				command.option[0] = 'v';
			break;
		}
		i++;
	}
	return (command);
}

t_command	parsing(int argc, char **argv)
{
	t_command	command;
	int			i;

	if (argc == 1)
	{
		command.status = 64;
		fprintf(stderr, "ft_ping: missing host operand\nTry 'ping -?' for more information.\n");
		return (command);
	}
	//print help:	- if encounter ? without having invalid options placed BEFORE ("-v?" || "-v -?")
	command.status = 0;
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
		if (command.status)
			break;
		i++;
	}
	return (command);
}
