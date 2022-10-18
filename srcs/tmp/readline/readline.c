/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:17:58 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/17 18:00:04 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/readline.h"

void	init_prompt(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

static void	exit_shell(void)
{
	printf("exit\n");
	// printf("\e[1A\e[11Cexit\n");
	exit(g_status);
}

char	*read_line_from_prompt(void)
{
	char	*str;

	str = readline("minishell$ ");
	if (!str)
		exit_shell();
	else if (ft_strlen(str) == 0)
	{
		free(str);
		return (NULL);
	}
	add_history(str);
	return (str);
}
