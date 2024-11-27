#include "ft_ping.h"

int	main(int argc, char **argv)
{
	t_command	command;

	command = parsing(argc, argv);	
	if (command.status)
		return (command.status);
	command.status = ft_ping(command);
	return command.status;	
}
