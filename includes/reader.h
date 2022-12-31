/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:27:39 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 17:10:11 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

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
void	slistadd(t_str **head, t_str *new);
void	free_slist(t_str *head);
void	sort_red_cmd(t_list *list);
bool	str_to_aim(t_str *lexical_line);
void	str_to_cmd(t_str **lexical_line);
t_list	*str_to_list(t_str *head);
bool	check_line(char *line);
bool	match_quote(char *str, size_t *i, char quote);
bool	match_bracket(char *str, size_t *i);
t_order	*make_command(t_type type, char **cmd, char *file, t_list *shell);
#endif