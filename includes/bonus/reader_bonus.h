/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:27:39 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/04 21:35:12 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_BONUS_H
# define READER_BONUS_H

# include "define.h"

bool	is_se(char c);
bool	is_dse(char c);
bool	is_bracket(const char c);
bool	is_redirect(t_type type);
void	cutline(t_str **lexical_line, char *line, int *i, int *str_len);
void	list_to_subshell(t_list **list);
void	free_list(t_list *head);
char	**make_cmd(t_str *start, t_str *last, int cnt);
t_str	*make_slistcmd(char **cmd);
t_list	*reader(char *line);
void	free_slist(t_str *head);
void	sort_red_cmd(t_list *list);
bool	str_to_aim(t_str *lexical_line);
void	str_to_cmd(t_str **lexical_line);
t_list	*str_to_list(t_str *head);
bool	check_line(char *line);
bool	match_quote(char *str, size_t *i, char quote);
bool	match_bracket(char *str, size_t *i);
t_order	*make_command(t_type type, char **cmd, char *file, t_list *shell);
bool	sort_shell_cmd(t_list *list);
void	free_sliststr(t_str *start, t_str *last);
void	free_slistall(t_str *head);
void	slistadd(t_str **head, t_str *add);
bool	check_lex(t_str	*current);
void	sort_red_str(t_str *list);
t_str	*slistlast(t_str *list);
t_list	*free_line(char *line);
#endif