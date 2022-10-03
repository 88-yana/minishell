/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:00:02 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/03 14:32:39 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divide_quote.h"
#include "../../lexer/lexer.h"
char	**partite(char *str)
{
	t_array	data;
	t_array	*array;
	// char	**ret;
	// bool	is_quote;
	// size_t	i;
	// char	**divide_array;

	data.line = str;
	array = lexer_re(&data);
	// i = 0;
	// while (array->array[i] != NULL)
	// {
	// 	divide_array = lexer(array->array[i]);
	// 	aad_array(ret, divide_array);
	// 	i++;
	// }
	return (array->array);
	
}

char	**arrayjoin(char **arr1, char**arr2)
{
	size_t	length;
	size_t	i;
	size_t	j;
	char	**new;

	length = arraylen(arr1) + arraylen(arr2) + 1;
	new = malloc(sizeof(char *) * length);
	i = 0;
	while (arr1[i] != NULL)
	{
		new[i] = arr1[i];
		i++;
	}
	j = 0;
	while (arr2[j] != NULL)
	{
		new[i + j] = arr2[j];
		j++;
	}
	new[length] = NULL;
	i = 0;
	return (new);
}

char	**combine_array(char **array, char **redirects, size_t *i)
{
	size_t	length;
	size_t	j;
	size_t	k;
	char	**new;

	length = arraylen(array) + arraylen(redirects) + 1;
	new = malloc(sizeof(char *) * length);
	j = 0;
	while (j <= *i)
	{
		new[j] = array[j];
		j++;
	}
	k = 0;
	j--;
	while (redirects[k] != NULL)
	{
		new[j + k] = redirects[k];
		k++;
	}
	(*i)++;
	while (array[*i] != NULL)
	{
		new[j + k] = array[*i];
		j++;
		(*i)++;
	}
	return (new);
}

char	**divide_redirect(char **array)
{
	size_t	i;
	char	**redirections;
	char	**ret;

	i = 0;
	while (array[i] != NULL)
	{
		redirections = partite(array[i]);
		ret = combine_array(array, redirections, &i);
		// return (ret);
		i++;
	}
	return (ret);
}

#include	"../main.h"
#include	"../../lexer/lexer.h"

t_list	*to_parser(char **array);

int	main(void)
{
	t_array	data;
	t_array	*box;
	char	**array;
	while (true)
	{
		data.line = exec_readline();
		if (data.line == NULL)
			continue ;
		box = lexer(&data);
		if (box == NULL)
			continue ;
		array = divide_redirect(box->array);
		int i = 0;
		while (array[i] != NULL)
		{
			printf("『%s』\n", array[i]);
			i++;
		}
	}
	return (0);
}