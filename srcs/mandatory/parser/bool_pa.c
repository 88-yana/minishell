/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:15:25 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/19 12:36:25 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_delimiter(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "&&") == 0)
		return (true);
	if (ft_strcmp(str, "||") == 0)
		return (true);
	return (false);
}

bool	is_bra(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "(") == 0)
		return (true);
	if (ft_strcmp(str, ")") == 0)
		return (true);
	return (false);
}

bool	is_pipe(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "|") == 0)
		return (true);
	return (false);
}

bool	is_redirection(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "<") == 0)
		return (true);
	if (ft_strcmp(str, ">") == 0)
		return (true);
	if (ft_strcmp(str, ">>") == 0)
		return (true);
	if (ft_strcmp(str, "<<") == 0)
		return (true);
	return (false);
}
