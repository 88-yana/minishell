/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:55:22 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/03 09:23:48 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_BONUS_H
# define BUILTIN_BONUS_H

# include	<errno.h>
# include	"../../libft/libft.h"
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
