/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:31:19 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/01 14:12:47 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char			*content;
	char			**content2;
	struct s_list	*next;
}	t_list;

void	print_list(t_list **lst);
void	print_command(t_list **lst);

int		is_token(char c);
char	*ft_strchr(char *s, int c);
t_list	*lexer(char *line);
t_list	*lexer2(char *readline, t_list *lst);

t_list	*expansion(t_list **token, char **envp);

int		ft_strlen(char *str);
int		ft_strslen(char **str);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_char(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);

t_list	*substitution(t_list **token, char **envp);

t_list	*remove_quote(t_list **token);

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strndup(char *s, size_t size);

t_list	*init_list(t_list *list);
t_list	*ft_lstnew(char *content, int len);
int		is_empty(t_list *list);
void	add_tail(t_list *list, t_list *new);
void	ft_lstclear(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

int		is_token(char c);
int		is_redirection(char c);

char	**ft_split(char const *s, char c);
int		test_flag(int flag, char content);

char	**ft_split_quote(char const *s, char *sep);
int		is_sep(char c, char *sep);
void	*ft_free_all(char **strs, int i);
void	*free_split_p(char **strs);

int		start_pipe(char *str);
int		test_multi(char *str);
char	check_triple(char *s);
int		end_pipe(char *str);

char	**split_redirect(char *s, char *sep);
char	**realoc_split(char **s);
char	**realoc_split2(char **s);
int		check_redirection_end(char **split);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_char(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
int		is_alpha(char c);
int		is_valid_variable(char c);
char	*check_variable(char *str, char **envp);
int		need_expand(char *str);
char	*expand_with_cote(char *str, char c);

char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	**get_path_line(char **envp);
char	*ft_strjoin2(char *s1, char *s2);
void	*free_split_s(char **split, int i);

char	*check_file_exist(char *command);
char	*command_sub(char *str, char **envp);

#endif