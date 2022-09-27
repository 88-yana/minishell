/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:20:08 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/27 19:56:41 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>
# include	<unistd.h>
# include	<sys/wait.h>
# include	<signal.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<errno.h>
# include	"../../../libft/libft.h"
# include	"../main/main.h"
# include	"../command_line/comline.h"

void	exec_pwd(t_vars *vars);
void	exec_exit(void);

#endif
