#include "minishell.h"

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

char	***big_join(t_list *lst)
{
	char	***res;
	int		size;
	int		i;

	size = ft_lstsize(lst);
	res = (char ***)malloc(sizeof(char **) * (size + 1));
	i = 0;
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = lst->content2;
		lst = lst->next ;
		i++;
	}
	res[i] = 0;
	return (res);
}

int main(int ac, char **av, char **envp)
{
	get_shell();
	get_shell()->envp = ft_envdup(envp);
	get_shell()->cmds = big_join(parsing(get_shell()->envp));
	ft_pipe(get_shell()->cmds, get_shell()->envp);
}
