#include "minishell.h"

void	ft_main_exit(t_shell *shell, int code)
{
	if (shell)
	{
		ft_dict_free(shell->env);
		free(shell);
	}
	exit(1);
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

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		write(1, map[i], ft_strlen(map[i]));
		write(1, "\n", 1);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = get_shell();
	shell->envp = ft_envdup(envp);
	ft_main_exit(shell, 0);
}
