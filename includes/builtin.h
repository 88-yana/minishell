/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:55:22 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 17:55:50 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include	<errno.h>
# include	"../libft/libft.h"
# include	"define.h"
# include	"envs.h"

bool	is_builtin(char **cmd);
void	exec_builtin(t_vars *vars, char **cmd);
void	exec_echo(char **cmd);
void	exec_cd(t_vars *vars, char **cmd);
void	exec_pwd(void);
void	exec_export(t_vars *vars, char **cmd);
void	exec_unset(t_vars *vars, char **cmd);
void	exec_env(t_vars *vars);
void	exec_exit(char **cmd);
void	exec_single_builtin(t_vars *vars, t_order *order);

#endif
