/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:56:35 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/19 11:39:45 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

int	pwd(void)
{
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) 
       printf("%s\n", cwd); 
	else 
   {
       perror("getcwd() error");
	   g_shell->exit_value = 2;
       return (1);
   }
   return (0);
}