/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:36:50 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/26 19:17:55 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"

void	exit_shell(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 128 + SIGINT;
	exit(0);
}

char	*exec_readline(void)
{
	char	*str;

	signal(SIGINT, exit_shell);
	signal(SIGINT, exit_shell);
	str = readline("minishell$ ");
	if (str == NULL)
		return (NULL);
	add_history(str);
	return (str);
}
