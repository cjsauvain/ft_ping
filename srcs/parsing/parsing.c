#include "ft_ping.h"

static void	get_ping_opt(bool *verbose_mode, char *opt)
{
	int	i = 1;

	while (opt[i])
	{
		if (opt[i] != 'v')
			display_invalid_option_and_exit(opt);
		else
		{
			*verbose_mode = true;
			return ;
		}
		i++;
	}
}

t_ping	parsing(int argc, char **argv, int *first_addr_index)
{
	t_ping	ping;
	int		i;

	if (argc == 1)
		display_missing_operand_and_exit();
	ping = initialize_ping_struct();
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] == '?')
			display_help_and_exit();
		else if (argv[i][0] == '-')
			get_ping_opt(&ping.verbose_mode, argv[i]);
		else if (!*first_addr_index)
			*first_addr_index = i;
		i++;
	}
	if (argc == 2 && ping.verbose_mode == true)
		display_missing_operand_and_exit();
	return ping;
}
