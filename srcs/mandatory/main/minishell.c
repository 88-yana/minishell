/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:22:57 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/26 12:35:53 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	main(void)
{
	t_vars	vars;

	vars.tree = malloc(sizeof(t_tree));
	vars.tree->type = COMMAND_LINE;
	vars.tree->line = NULL;
	while (1)
	{
		vars.tree->line = readline("minishell$ ");
		if (vars.tree->line == NULL || strlen(vars.tree->line) == 0)
		{
			free(vars.tree->line);
			break ;
		}
		add_history(vars.tree->line);
		handle_parser(vars.tree);
		free(vars.tree->line);
	}
	return (0);
}

//int	main(int argc, char **argv, char **envp)
//{
//	if (argc > 1)
//		execve("/bin/echo", &argv[1], envp);
//	return (0);
//}
