/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:35:11 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/17 20:21:32 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/envs.h"

void	convert_envp_to_list(t_vars *vars, char **envp)
{
	size_t	i;

	vars->envs = NULL;
	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		create_envs_list(vars, envp[i]);
		i++;
	}
}
