#include "ft_ping.h"

static int	get_list_length(char **list)
{
	int	i;

	i = 0;
	if (!list)
		return 0;
	while (list[i])
		i++;
	return i;
}

static char	**allocate_memory(char **list)
{
	char	**new_list;
	int		list_len;

	list_len = get_list_length(list);
	if (!list)
		list_len++;
	new_list = realloc(list, (list_len + 1) * sizeof(char *));
	if (!list)
		new_list[0] = NULL;
	return new_list;
}

static void	update_list(char **list, char *new_addr)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	list[i] = new_addr;
	list[i + 1] = NULL;
}

char	**update_addr_list(char **list, char *new_addr)
{
	list = allocate_memory(list);
	update_list(list, new_addr);

	return list;
}
