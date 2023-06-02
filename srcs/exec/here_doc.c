#include "exec.h"

int	is_valid_variable(char c)
{
	if ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
			|| ('0' <= c && c <= '9') || c == '_'))
		return (1);
	return (0);
}

t_list	*here_doc_write(t_list *docs, t_list *input, char *eof, int fd)
{
	char	*tmp;
	char	*str;
	int		i;

	while (input && !ft_strcmp(input->content, eof))
	{
		i = 0;
		str = input->content;
		while (str[i])
		{
			if (str[i] == '$')
			{
				tmp = ft_env_sub(str + 1 + i++);
				write(fd, tmp, ft_strlen(tmp));
				while (str[i] && is_valid_variable(str[i]))
					i++;
			}
			else
				write(fd, str + i++, 1);
		}
		if (str)
			write(fd, "\n", 1);
		input = input->next;
	}
	return (close(fd), docs);
}

t_list	*here_doc_open(t_list *docs, t_list *input, char *eof)
{
	char	*str;
	int		fd;
	int		i;

	i = 0;
	fd = -1;
	str = NULL;
	while (fd == -1)
	{
		if (str)
			free(str);
		str = ft_strjoin(ft_strdup(".here_doc"), ft_itoa(i++));
		fd = open(str, O_CREAT + O_EXCL + O_RDWR, 0666);
	}
	ft_lstadd_back(&docs, ft_lstnew(str));
	return (here_doc_write(docs, input, eof, fd));
}

t_list	*here_doc_aux(t_list *docs, char **cmd, int x)
{
	t_list	*input;
	int		i;

	i = 0;
	input = NULL;
	ft_lstadd_back(&input, ft_lstnew(readline(">")));
	while (!ft_strcmp(ft_lstlast(input)->content, cmd[x + 1])
		&& ft_lstlast(input)->content)
	{
		ft_lstadd_back(&input, ft_lstnew(readline(">")));
		i++;
	}
	if (!ft_lstlast(input)->content)
	{
		write(2, "warning : here-document at line ", 33);
		ft_putnbr_fd(2, i);
		write(2, " delimited by end-of-file (wanted `", 36);
		write(2, cmd[x + 1], ft_strlen(cmd[x + 1]));
		write(2, "')\n", 3);
	}
	docs = here_doc_open(docs, input, cmd[x + 1]);
	ft_lst_free(input);
	cmd[x] = "<";
	cmd[x + 1] = ft_lstlast(docs)->content;
	return (docs);
}

t_list	*here_doc(char ***cmds)
{
	t_list	*docs;
	int		i;
	int		j;

	i = 0;
	docs = NULL;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (ft_strcmp(cmds[i][j], "<<"))
				docs = here_doc_aux(docs, cmds[i], j);
			j++;
		}
		i++;
	}
	return (docs);
}
