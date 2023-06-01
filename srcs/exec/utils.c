#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_strcpy(char *src, char *dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == s2[i]);
}

char	*ft_strdup(char *str, int size)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		ft_main_exit(get_shell(), 1);
	i = 0;
	while (str[i] && size)
	{
		res[i] = str[i];
		size--;
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_dict	*dicting(char **env)
{
	t_dict	*res;
	char	*key;
	char	*content;
	int		i;
	int		j;

	i = 0;
	res = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		key = ft_strdup(env[i], j);
		content = ft_strdup(env[i] + j + 1, ft_strlen(env[i] + j + 1));
		ft_dictadd_back(&res, ft_dictnew(key, content));
		i++;
	}
	return (res);
}

void	*free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	return (NULL);
}

char	**maping(t_dict *dict)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_dictsize(dict) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (dict)
	{
		res[i] = malloc(ft_strlen(dict->key) + ft_strlen(dict->content) + 2);
		if (!res)
			return (free_map(res));
		ft_strcpy(dict->key, res[i]);
		res[i][ft_strlen(dict->key)] = '=';
		ft_strcpy(dict->content, res[i] + (ft_strlen(dict->key) + 1));
		res[i][ft_strlen(dict->key) + ft_strlen(dict->content) + 1] = '\0';
		dict = dict->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
