#include "exec.h"

int	main(int ac, char **av, char **envp)
{
	char	*echo[10] = {"echo", "Hello 42.", ">>", "test", ">>", "llll", NULL};
	char	*cat[5] = {"/usr/bin/cat", "<<", "EOF"};
	char	*ls[5] = {"/usr/bin/ls", "..", NULL};
	char	*trash[2] = {"blablabla", NULL};
	char	*wc[3] = {"/bin/wc", "-l", NULL};
	char	*grep[3] = {"/usr/bin/grep", "dict", NULL};
	char	*touch[3] = {"/usr/bin/touch", "lol", NULL};
	char	*rm[4] = {"/usr/bin/rm", "-f", "lol", NULL};
	char	**cmds[6] = {ls, cat, wc, NULL};

	get_shell();
	get_shell()->envp = ft_envdup(envp);
	t_list *lst = here_doc(cmds);
	ft_pipe(cmds, envp);
	t_list *tmp = lst;
	while (tmp)
	{
		// unlink(tmp->content);
		tmp = tmp->next;
	}
	ft_lst_free(lst);
	(void)ac;
	(void)av;
	(void)cat;
	(void)echo;
	(void)envp;
	(void)ls;
	(void)trash;
	(void)wc;
	(void)grep;
	(void)touch;
	(void)rm;
	(void)cmds;
}