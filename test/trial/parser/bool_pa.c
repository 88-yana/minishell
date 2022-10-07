/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:15:25 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/07 15:13:19 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

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
