/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:49:46 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/02 16:29:29 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_angle_bracket(char c)
{
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	return (false);
}

static bool	is_cketbra(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str) - 1)
	{
		if (str[i] == '>' && str[i + 1] == '<')
			return (false);
		i++;
	}
	return (true);
}

bool	check_arguments(char *str)
{
	size_t	i;
	size_t	quote;
	bool	during_quotes;
	

	during_quotes = false;
	i = 0;
	quote = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == DUBLEQ)
			during_quotes = !during_quotes;
		if (during_quotes == false && is_angle_bracket(str[i]))
			quote++;
		else
			quote = 0;
		if (quote == 3)
			return (false);
		i++;
	}
	return (is_cketbra(str));
}


// #include	"main.h"
// #include	"../lexer/lexer.h"

// t_list	*to_parser(char **array);

// int	main(void)
// {
// 	char	*str;
// 	while (true)
// 	{
// 		str = exec_readline();
// 		if (str == NULL)
// 			continue ;
// 		printf("%s\n", str);
// 		printf("ans is %s\n", check_arguments(str) ? "true" : "false");
// 	}
// }