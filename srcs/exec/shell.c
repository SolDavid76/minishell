#include "exec.h"

void	ft_main_exit(int code)
{
	t_shell	*shell;

	shell = get_shell();
	if (shell)
	{
		free_tab(shell->envp);
		free_tab_tab(shell->cmds);
		free(shell);
	}
	exit(code);
}

t_shell	*get_shell(void)
{
	static t_shell	*shell = NULL;

	if (shell)
		return (shell);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(1);
	return (shell);
}

char	**ft_envdup(char **envp)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_tablen(envp) + 1));
	if (!res)
		exit(1);
	i = -1;
	while (envp[++i])
		res[i] = ft_strdup(envp[i]);
	res[i] = NULL;
	return (res);
}

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
