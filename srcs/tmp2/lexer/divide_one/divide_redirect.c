// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   divide_redirect.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/10/02 17:00:02 by hyanagim          #+#    #+#             */
// /*   Updated: 2022/10/03 18:02:00 by hyanagim         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "divide.h"
// #include "../../lexer/lexer.h"

// char	**divide_redirect(char **array)
// {
// 	size_t	i;
// 	char	**redirections;
// 	char	**ret;
// 	t_array	data;

// 	ret = malloc(sizeof(char *));
// 	ret[0] = NULL;
// 	i = 0;
// 	while (array[i] != NULL)
// 	{
// 		data.line = array[i];
// 		redirections = lexer_re(&data);
// 		ret = arrayjoin(ret, redirections);
// 		i++;
// 	}
// 	return (ret);
// }

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
// 		array = divide_redirect(box->array);
// 		i = 0;
// 		while (array[i] != NULL)
// 		{
// 			printf("『%s』\n", array[i]);
// 			i++;
// 		}
// 	}
// 	return (0);
// }
