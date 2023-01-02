/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:53:00 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/01 14:47:14 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVS_BONUS_H
# define ENVS_BONUS_H

# include	"../libft/libft.h"
# include	"define.h"
# include	"utils.h"

# define DQ 0
# define SQ 1

t_list	*find_envs(t_list *list, char *to_find);
bool	create_envs_list(t_vars *vars, char *str);
t_envs	*create_envs(char *type, char *value);
void	add_to_envs(t_envs *envs, char *value);
void	replace_envs(t_envs *envs, char *value);
void	create_list(t_list **list, t_envs *envs);
void	free_envs(void *p);
void	convert_envp_to_list(t_vars *vars, char **envp);
char	**get_envp_from_list(t_list *list);
char	*lexer_envs(t_vars *vars, char *line);

#endif
