/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:00:02 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/04 16:56:03 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "divide_quote.h"

// char	**partite(char *str)
// {
// 	t_array	data;
// 	t_array	*array;
// 	char	**ret;
// 	bool	is_quote;
// 	size_t	i;
// 	char	**divide_array;

// 	array = lexer_re(&data);
// 	i = 0;
// 	while (array->array[i] != NULL)
// 	{
// 		divide_array = lexer(array->array[i]);
// 		aad_array(ret, divide_array);
// 		i++;
// 	}
	
	
// }

// t_list	*divide_redirect(char **array)
// {
// 	size_t	i;
// 	char	**redirections;

// 	i = 0;
// 	while (array[i] != NULL)
// 	{
// 		if (find_redirection(array[i]))
// 		{
// 			redirections = partite(array[i]);
// 			combine_array(array, redirections, i);
// 		}
// 		i++;
// 	}
// }

// #include	"../main.h"
// #include	"../../lexer/lexer.h"

// t_list	*to_parser(char **array);

// int	main(void)
// {
// 	t_array	data;
// 	t_array	*array;
// 	while (true)
// 	{
// 		data.line = exec_readline();
// 		if (data.line == NULL)
// 			continue ;
// 		array = lexer_re(&data);
// 		if (array == NULL)
// 			continue ;
		
// 		int i = 0;
// 		while (array->array[i] != NULL)
// 		{
// 			printf("『%s』\n", array->array[i]);
// 			i++;
// 		}
// 	}
// }