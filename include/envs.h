/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:53:00 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/03 21:03:04 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVS_H
# define ENVS_H

# include	"../libft/libft.h"
# include	"structure.h"
# include	"utils.h"

t_list	*find_envs(t_list *list, char *to_find);
bool	create_envs_list(t_list **list, char *str);
void	convert_envp_to_list(t_vars *vars, char **envp);
char	**get_envp_from_list(t_list *list);

#endif
