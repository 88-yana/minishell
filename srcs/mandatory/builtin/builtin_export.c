/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:00:24 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/01 17:02:49 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/builtin.h"

void	exec_export(t_vars *vars, char **cmd)
{
	if (ft_strcmp(cmd[0], "pwd"))
		return ;
	
}
