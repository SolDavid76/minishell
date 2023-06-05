#include "minishell.h"

void	free_tab(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	free_tab_tab(char ***ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free_tab(ptr[i++]);
	free(ptr);
}
