/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:56:08 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/17 17:57:52 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/minishell.h"

g_status = 0;

static void	test(t_vars *vars, char *str)
{
	size_t	i;
	char	**cmd;

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

static void	minishell(char **envp)
{
	t_vars	vars;
	char	*str;

	init_setup(&vars, envp);
	while (true)
	{
		str = read_line_from_prompt();
		if (!str)
			continue ;
		test(&vars, str);
		free(str);
	}
	ft_lstclear(&vars.envs, free_envs);
}

// __attribute__((destructor))
// static void	destructor(void)
// {
// 	system("leaks -q minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
