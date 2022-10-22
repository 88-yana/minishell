/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:36:50 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/29 21:32:26 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"

void	exit_shell(void)
{
	printf("\e[1A\e[11Cexit\n");
	exit(g_status);
}

void	init_prompt(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	closed(int signal)
{
	// close(STDIN_FILENO);
}

char	*unclosed_pipe(void)
{
	char	*str;
	int		pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		signal(SIGINT, closed);
		while (true)
		{
			str = readline("> ");
			if (!str)
				return (NULL);
			else if (ft_strlen(str) != 0)
				break ;
			free(str);
		}
	}
	wait(NULL);
	return (str);
}

char	*exec_readline(void)
{
	char	*str;
	char	*buf;

	signal(SIGINT, init_prompt);
	signal(SIGQUIT, SIG_IGN);
	str = readline("minishell$ ");
	if (!str)
		exit_shell();
	else if (ft_strlen(str) == 0)
		return (NULL);
	add_history(str);
	// buf = unclosed_pipe();
	// str = ft_strjoin(str, buf);
	// printf("%s\n", str);
	return (str);
}
