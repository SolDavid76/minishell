#include "minishell.h"

void	ft_dict_del(t_dict *dict)
{
	if (dict)
	{
		free(dict->key);
		free(dict->content);
		free(dict);
	}
}

void	ft_dict_free(t_dict	*dict)
{
	t_dict	*tmp;

	while (dict)
	{
		tmp = dict->next;
		free(dict->key);
		free(dict->content);
		free(dict);
		dict = tmp;
	}
}
