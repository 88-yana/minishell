/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:55:22 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/22 19:25:39 by hyanagim         ###   ########.fr       */
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
void	exec_pwd(char **cmd);
void	exec_export(t_vars *vars, char **cmd);
void	exec_unset(t_vars *vars, char **cmd);
void	exec_env(t_vars *vars, char **cmd);
void	exec_exit(char **cmd);

#endif
