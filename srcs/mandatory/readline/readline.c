/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:17:58 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/28 21:24:56 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/readline.h"

static void	exit_shell(void)
{
	printf("\e[1A\e[11Cexit\n");
	exit(0);
}

static void	init_prompt(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*read_line_from_prompt(void)
{
	char	*str;

	signal(SIGINT, init_prompt);
	signal(SIGQUIT, SIG_IGN);
	str = readline("minishell$ ");
	if (!str)
		exit_shell();
	else if (ft_strlen(str) == 0)
		return (NULL);
	add_history(str);
	return (str);
}
