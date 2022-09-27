/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:22:57 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/27 20:25:57 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	t_list	*command_line;
	char	*str;

	(void)argc;
	(void)argv;

	vars.envs_list = NULL;
	convert_envp_to_list(&vars, envp);
	while (true)
	{
		str = exec_readline();
		check_comline(command_line);
		exec_comline(&vars, command_line);
		free(str);
		break ;
	}
}
