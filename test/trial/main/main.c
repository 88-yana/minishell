/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:10:45 by yahokari          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/07 18:17:10 by yahokari         ###   ########.fr       */
=======
/*   Updated: 2022/10/06 21:10:14 by hyanagim         ###   ########.fr       */
>>>>>>> 8d81291fc0f3c540711157d457315818c07108dd
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"
#include	"../lexer/lexer.h"

t_list	*to_parser(char **array);

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	t_list	*command_line;
	t_array	data;
	t_array	*array;
	char	**abc;

	(void)argc;
	(void)argv;
	vars.envs_list = NULL;
	convert_envp_to_list(&vars, envp);
	while (true)
	{
		data.line = exec_readline();
		if (data.line == NULL)
			continue ;
		array = lexer(&data);
		if (array == NULL)
			continue ;
		abc = divide_redirect(array->array);
		command_line = to_parser(abc);
		if (command_line == NULL)
			continue ;
		check_comline(command_line);
		exec_comline(&vars, command_line);
		free(data.line);
	}
}
