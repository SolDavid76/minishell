#include "minishell.h"

t_dict	*ft_dictnew(char *key, char *content)
{
	t_dict	*res;

	res = malloc(sizeof(t_dict));
	if (!res)
		ft_main_exit(get_shell(), 1);
	res->key = key;
	res->content = content;
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

int	ft_dictsize(t_dict *dict)
{
	int	i;

	i = 0;
	while (dict)
	{
		dict = dict->next;
		i++;
	}
	return (i);
}

t_dict	*ft_dictlast(t_dict *dict)
{
	while (dict)
	{
		if (dict->next == NULL)
			return (dict);
		dict = dict->next;
	}
	return (dict);
}

void	ft_dictadd_back(t_dict **dict, t_dict *new)
{
	t_dict	*last;

	if (dict)
	{
		if (*dict)
		{
			last = ft_dictlast(*dict);
			new->prev = last;
			last->next = new;
		}
		else
			*dict = new;
	}
}

t_dict	*ft_dict_find(t_dict *dict, char *key)
{
	while (dict)
	{
		if (ft_strcmp(dict->key, key))
			return (dict);
		dict = dict->next;
	}
	return (NULL);
}
