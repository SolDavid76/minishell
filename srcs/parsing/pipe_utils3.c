/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:59:29 by ennollet          #+#    #+#             */
/*   Updated: 2023/05/26 18:08:26 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	test_multi(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			flag = 1;
			while (is_space(str[i]) == 1 || str[i] == '|')
			{
				i++;
				if (flag == 1 && str[i] == '|')
					return (1);
			}
		}
		flag = 0;
		i++;
	}
	return (0);
}

int	end_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			while (str[i] && (is_space(str[i]) || str[i] == '|'))
				i++;
			if (str[i] == '\0')
				return (1);
		}
	i++;
	}
	return (0);
}

int	start_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '|')
		return (1);
	else
		return (0);
}

char	check_triple(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			if (s[i + 1] && s[i + 1] == s[i] && s[i + 2] && s[i + 2] == s[i])
				return (s[i + 2]);
		i++;
	}
	return (0);
}
