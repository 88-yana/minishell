/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:17:58 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 17:47:07 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"

static void	init_prompt(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

static void	setup_signal(void)
{
	signal(SIGINT, init_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	exit_shell(void)
{
	printf("exit\n");
	exit(g_status);
}

static void	do_nothing(int signal)
{
	(void)signal;
}

char	*read_line_from_prompt(void)
{
	char	*str;

	setup_signal();
	str = readline(PROMPT);
	signal(SIGINT, do_nothing);
	if (str == NULL)
		exit_shell();
	else if (ft_strlen(str) == 0)
	{
		free(str);
		return (NULL);
	}
	add_history(str);
	return (str);
}
