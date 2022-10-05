// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   divide_redirect.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/10/02 17:00:02 by hyanagim          #+#    #+#             */
// /*   Updated: 2022/10/03 17:19:33 by hyanagim         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "divide_quote.h"
#include "../../lexer/lexer.h"
#include "../divider/divide.h"

char	**divide_redirect(char **array)
{
	size_t	i;
	char	**redirections;
	char	**half;
	t_array	data;
	char	**brackets;
	// char	**array;
	char	**ret;

	half = malloc(sizeof(char *));
	half[0] = NULL;
	i = 0;
	while (array[i] != NULL)
	{
		data.line = array[i];
		redirections = lexer_re(&data);
		printf("redirections is 「%s」\n", redirections[0]);
		half = arrayjoin(half, redirections);
		i++;
	}
	// return (half);
	ret = malloc(sizeof(char *));
	ret[0] = NULL;
	i = 0;
	while (half[i] != NULL)
	{
		data.line = half[i];
		brackets = lexer_div(&data);
		// brackets = delete_brank(brackets);
		printf("brackets is %s\n", brackets[0]);
		ret = arrayjoin(ret, brackets);
		i++;
	}
	return (ret);
}

// #include	"../../main/main.h"

// t_list	*to_parser(char **array);

// int	main(void)
// {
// 	t_array	data;
// 	t_array	*box;
// 	char	**array;
// 	size_t	i;

// 	while (true)
// 	{
// 		data.line = exec_readline();
// 		if (data.line == NULL)
// 			continue ;
// 		box = lexer(&data);
// 		if (box == NULL)
// 			continue ;
// 		i = 0;
// 		while (box->array[i] != NULL)
// 		{
// 			printf("『%s』\n", box->array[i]);
// 			i++;
// 		}
// 		array = divide_redirect(box->array);
// 		i = 0;
// 		printf("%s\n", "----------------------");
// 		while (array[i] != NULL)
// 		{
// 			printf("『%s』\n", array[i]);
// 			i++;
// 		}
// 	}
// 	return (0);
// }
