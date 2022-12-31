/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:20:29 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 17:20:31 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef READLINE_H
# define READLINE_H

# include	<stdio.h>
# include	<signal.h>
# include	<stdbool.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../libft/libft.h"
# include	"define.h"

# define PROMPT "minishell$ "

char	*read_line_from_prompt(void);

#endif
