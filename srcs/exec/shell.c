#include "exec.h"

char	*ft_env_sub(char *key)
{
	char	**envp;
	int		i;
	int		j;

	i = 0;
	envp = get_shell()->envp;
	while (envp[i])
	{
		j = 0;
		while (key[j] == envp[i][j] && is_valid_variable(key[j]))
			j++;
		if (!is_valid_variable(key[j]) && envp[i][j] == '=')
			return (envp[i] + j + 1);
		i++;
	}
	return (NULL);
}
