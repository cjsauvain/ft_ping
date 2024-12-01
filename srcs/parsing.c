#include "ft_ping.h"

static void	display_error_message(void)
{
	fprintf(stderr, "ft_ping: missing host operand\n");
	fprintf(stderr, "Try 'ping -?' for more information.\n");
	exit(64);
}

static void	display_help(void)
{
	//display_help;
	exit(0);
}

static void	get_option(t_command *command, char *option)
{
	int	i = 1;

	while (option[i])
	{
		if (option[i] != 'v')
			display_error_message();
		else
			command->option[0] = 'v';
		i++;
	}
}

t_command	parsing(int argc, char **argv)
{
	t_command	command;
	int			i;

	if (argc == 1)
		display_error_message();
	command.option[0] = '0';
	command.option[1] = '\0';
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] == '?')
			display_help();
		else if (argv[i][0] == '-')
			get_option(&command, argv[i]);
		command.addr = update_addr_list(command.addr, argv[i]);
		i++;
	}
	return command;
}
