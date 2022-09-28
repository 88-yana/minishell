/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:18:45 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/28 21:33:37 by yahokari         ###   ########.fr       */
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
# include	"../libft/libft.h"
# include	"structure.h"

char	*read_line_from_prompt(void);

#endif
