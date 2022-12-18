/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:02:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/18 14:37:20 by hyanagim         ###   ########.fr       */
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
		// system("leaks -q minishell");
		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
		// system("leaks -q minishell");
		vars.array = lexer(vars.line);
		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
		// system("leaks -q minishell");
		if (vars.array == NULL)
			continue ;
		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
		// system("leaks -q minishell");
		vars.comline = parser(vars.array);
		if (vars.comline == NULL)
			continue ;
		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
		// system("leaks -q minishell");
		execution(&vars);
		free_doubleptr(vars.array);
		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
		// system("leaks -q minishell");
		ft_lstclear(&(vars.comline), free);
		free(vars.line);
		// system("leaks -q minishell");
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
