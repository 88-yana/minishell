/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:02:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/11 19:26:17 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/minishell.h"

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
		vars.array = lexer(vars.line);
		if (vars.array == NULL)
			continue ;
		vars.comline = parser(vars.array);
		if (vars.comline == NULL)
			continue ;
		execution(&vars);
		free_doubleptr(vars.array);
		ft_lstclear(&(vars.comline), free);
		free(vars.line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
