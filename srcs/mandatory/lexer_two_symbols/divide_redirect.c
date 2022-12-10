/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:00:02 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/21 03:31:20 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer_two_symbols.h"

char	**divide_by_duble(char **array)
{
	char	**half;
	size_t	i;
	t_array	data;
	char	**redirections;

	half = malloc(sizeof(char *));
	half[0] = NULL;
	i = 0;
	while (array[i] != NULL)
	{
		data.line = array[i];
		redirections = lexer_re(&data);
		half = arrayjoin(half, redirections);
		free(redirections);
		i++;
	}
	return (half);
}

char	**divide_by_one(char **half)
{
	size_t	i;
	t_array	data;
	char	**brackets;
	char	**ret;

	ret = malloc(sizeof(char *));
	ret[0] = NULL;
	i = 0;
	while (half[i] != NULL)
	{
		data.line = half[i];
		brackets = lexer_div(&data);
		brackets = delete_brank(brackets);
		ret = arrayjoin(ret, brackets);
		free(brackets);
		i++;
	}
	return (ret);
}

char	**divide_redirect(char **array)
{
	char	**half;
	char	**ret;
	half = divide_by_duble(array);
	ret = divide_by_one(half);
	// free_doubleptr(half);
	return (ret);
}
