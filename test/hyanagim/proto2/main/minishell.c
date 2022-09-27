/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:55:19 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/27 12:34:43 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../../../libft/libft.h"


// int	main(void)
// {
// 	t_vars	vars;

// 	vars.tree = malloc(sizeof(t_tree));
// 	vars.tree->line = NULL;
// 	while (1)
// 	{
// 		vars.tree->line = readline("minishell > ");
// 		if (vars.tree->line == NULL || strlen(vars.tree->line) == 0)
// 		{
// 			free(vars.tree->line);
// 			break ;
// 		}
// 		add_history(vars.tree->line);
// 		handle_parser(vars.tree);
// 		free(vars.tree->line);
// 	}
// 	return (0);
// }


int	main(void)
{
	t_list	*command_line;
	char	*line;
	char	**ult;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		printf("line is '%s'\n", line);
		add_history(line);
		ult = lexer(line);
		i = 0;
		while (ult[i] != NULL)
		{
			printf("%s\n", ult[i]);
			i++;
		}
		free(line);
	}
	printf("exit\n");
	return (0);
}
