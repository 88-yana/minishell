/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:20:29 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/03 09:24:22 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_BONUS_H
# define READLINE_BONUS_H

# include	<stdio.h>
# include	<signal.h>
# include	<stdbool.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../../libft/libft.h"
# include	"define.h"

# define PROMPT "minishell$ "

char	*read_line_from_prompt(void);

#endif
