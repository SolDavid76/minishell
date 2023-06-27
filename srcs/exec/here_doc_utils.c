/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:07:16 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/26 18:10:49 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	here_doc_error(char *eof, int lines)
{
	write(2, "warning : here-document at line ", 33);
	ft_putnbr_fd(2, lines);
	write(2, " delimited by end-of-file (wanted `", 36);
	write(2, eof, ft_strlen(eof));
	write(2, "')\n", 3);
}
