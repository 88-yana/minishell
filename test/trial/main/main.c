/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:10:45 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/28 18:24:35 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"
t_list	*to_parser(char **array);
t_array	*lexer(t_array	*data);

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	t_list	*command_line;
	t_array	data;
	t_array	*array;

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
		command_line = to_parser(array->array);
		check_comline(command_line);
		exec_comline(&vars, command_line);
		free(data.line);
	}
}