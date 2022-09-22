/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/22 15:36:17 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include "../main/minishell.h"

void	check_line(char *line)
{
	while (*line != '\0')
	{
		if (*line == '"')
		{
			line++;
			while (*line != '\0' && *line != '"')
				line++;
			if (*line == '\0')
				print_error("syntax error\n");
			else
				continue ;
		}
		if (*line == '\'')
		{
			line++;
			while (*line != '\0' && *line != '"')
				line++;
			if (*line == '\0')
				print_error("syntax error\n");
			else
				continue ;
		}
		line++;
	}
	return ;
}

char	**lexer(char *line)
{
	char	**temp;

	check_line(line);
	temp = lx_split(line, ' ');
	return (temp);
}
