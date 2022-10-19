/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:56:08 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/19 15:29:54 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/minishell.h"

#include	"../lexer/lexer.h"
#include	"../parser/parser.h"

g_status = 0;

static void	test(t_vars *vars, char *str)
{
	size_t	i;
	char	**cmd;

	if (!ft_strcmp("echo $?", str))
	{
		printf("%d\n", g_status);
		return ;
	}
	cmd = ft_split(str, ' ');
	exec_builtin(vars, cmd);
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

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

// static void	minishell(char **envp)
// {
// 	t_vars	vars;
// 	char	*str;

// 	init_setup(&vars, envp);
// 	while (true)
// 	{
// 		setup_signal();
// 		str = read_line_from_prompt();
// 		if (!str)
// 			continue ;
// 		test(&vars, str);
// 		free(str);
// 	}
// }

static void	minishell(char **envp)
{
	t_vars	vars;
	t_array	data;
	t_array	*array;
	t_list	*command_line;
	char	**buf;

	init_setup(&vars, envp);
	while (true)
	{
		setup_signal();
		data.line = read_line_from_prompt();
		if (!data.line)
			continue ;
		if (data.line == NULL)
			continue ;
		array = lexer(&data);
		if (array == NULL)
			continue ;
		buf = divide_redirect(array->array);
		command_line = to_parser(buf);
		if (command_line == NULL)
			continue ;
		// test(&vars, data.line);
		check_comline(command_line);
		exec_comline(&vars, command_line);
		free(data.line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
