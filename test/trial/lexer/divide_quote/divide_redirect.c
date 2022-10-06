/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:00:02 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/06 19:36:09 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divide_quote.h"
#include "../../lexer/lexer.h"
#include "../divider/divide.h"

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
	return (ret);
}

#include	"../../main/main.h"

t_list	*to_parser(char **array);

int	main(void)
{
	t_array	data;
	t_array	*box;
	char	**array;
	size_t	i;

	while (true)
	{
		data.line = exec_readline();
		if (data.line == NULL)
			continue ;
		box = lexer(&data);
		if (box == NULL)
			continue ;
		i = 0;
		while (box->array[i] != NULL)
		{
			printf("『%s』\n", box->array[i]);
			i++;
		}
		array = divide_redirect(box->array);
		i = 0;
		printf("%s\n", "----------------------");
		while (array[i] != NULL)
		{
			printf("『%s』\n", array[i]);
			i++;
		}
		printf("\n");
	}
	return (0);
}
