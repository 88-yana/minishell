/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:36:50 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/26 21:54:49 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"

void	exit_shell(void)
{
	printf("\e[1A\e[11Cexit\n");
	exit(0);
}

void	init_prompt(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*exec_readline(void)
{
	char	*str;

	signal(SIGINT, init_prompt);
	signal(SIGQUIT, SIG_IGN);
	str = readline("minishell$ ");
	if (!str)
		exit_shell();
	add_history(str);
	return (str);
}
