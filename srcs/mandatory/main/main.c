/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:02:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 18:57:38 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static void	minishell(char **envp)
{
	t_vars	vars;

	g_status = 0;
	convert_envp_to_list(&vars, envp);
	while (true)
	{
		vars.line = read_line_from_prompt();
		if (vars.line == NULL)
			continue ;
		vars.comline = reader(vars.line);
		system("leaks -q minishell");
		if (vars.comline == NULL)
			continue ;
		execution(&vars);
		free_list(vars.comline);
		system("leaks -q minishell");
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
