/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:55:22 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/03 21:22:58 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include	"../libft/libft.h"
# include	"structure.h"
# include	"envs.h"

bool	is_builtin(char **cmd);
void	exec_builtin(t_list *envs_list, char **cmd);
void	exec_echo(char **cmd);
void	exec_cd(t_list *list, char **cmd);
void	exec_pwd(char **cmd);
void	exec_export(t_list *list, char **cmd);
void	exec_exit(char **cmd);

#endif
