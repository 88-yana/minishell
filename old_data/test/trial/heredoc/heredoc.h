/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:52:02 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/22 19:16:22 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>
# include	<unistd.h>
# include	<sys/wait.h>
# include	<signal.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<errno.h>
# include	"../../../../libft/libft.h"
# include	"../main/main.h"
# include	"../command_line/comline.h"

void	check_comline(t_list *comline);

#endif
