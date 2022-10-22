/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:39:46 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/26 19:16:43 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>
# include	<unistd.h>
# include	<sys/wait.h>
# include	<signal.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../../../libft/libft.h"
# include	"../main/main.h"
# include	"../command_line/comline.h"

char	*exec_readline(void);

#endif