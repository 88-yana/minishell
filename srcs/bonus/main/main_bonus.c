/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:02:52 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/03 20:01:59 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell_bonus.h"

static void	minishell(char **envp)
{
	t_vars	vars;
	t_list	*list;

	g_status = 0;
	convert_envp_to_list(&vars, envp);
	while (true)
	{
		vars.line = read_line_from_prompt();
		if (vars.line == NULL)
			continue ;
		vars.comline = reader(vars.line);
		if (vars.comline == NULL)
			continue ;
		list = check_comline(vars.comline);
		if (!list)
			exec_comline(&vars, vars.comline);
		else
			heredoc_unlink(vars.comline, list);
		free_list(vars.comline);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
