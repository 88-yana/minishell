/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/21 17:32:21 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include "../main/minishell.h"

char	**lexer(char *line)
{
	char	**temp;

	temp = lx_split(line, ' ');
	return (temp);
}
