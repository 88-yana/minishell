/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:56:08 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/22 16:41:18 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/minishell.h"

#include	"../lexer/lexer.h"
#include	"../parser/parser.h"

g_status = 0;

static void	setup_signal(void)
{
	signal(SIGINT, init_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	init_setup(t_vars *vars, char **envp)
{
	convert_envp_to_list(vars, envp);
	setup_signal();
}

static void	minishell(char **envp)
{
	t_vars	vars;
	t_list	*command_line;
	char	**array;
	char	*line;

	init_setup(&vars, envp);
	while (true)
	{
		line = read_line_from_prompt();
		if (!line)
			continue ;
		array = lexer(line);
		if (!array)
			continue ;
		command_line = parser(array);
		if (command_line == NULL)
			continue ;
		check_comline(command_line);
		exec_comline(&vars, command_line);
		free(line);
		//free(array);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
