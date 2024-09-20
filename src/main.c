#include "ft_ping.h"

int	main(int argc, char **argv)
{
	t_command	command = parsing(argc, argv);
	
	if (command.status)
		return (command.status);
	command.status = ft_ping(command);
	//printf("command_status = %d\ncommand_ip_addr = %s\ncommand_option = %s\n",command.status, command.ip_addr, command.option);
	return (command.status);	
}
