/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/22 20:13:38 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include "../main/minishell.h"

static int	plus_pos(char *str, size_t *i, char c)
{
	(*i)++;

	if (str[*i] == c)
	{
		(*i)++;
		if (str[*i] == '\0')
			return (0);
		return (0);
	}
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	while (str[*i] != '\0' && str[*i] != ' ')
		(*i)++;
	return (1);
}

void	check_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			plus_pos(line, &i, '\"');
			if (line[i] == '\0')
				print_error("syntax error\n");
		}
		if (line[i] == '\'')
		{
			plus_pos(line, &i, '\'');
			if (line[i] == '\0')
				print_error("syntax error\n");
		}
		i++;
	}
	return ;
}

// typedef struct s_check
// {
// 	int		ok_line;
// 	int		ok_hairetu;
// 	char	**temp;
// }	t_check;


static size_t	count_size(char *str, char c)
{
	size_t	i;
	size_t	cnt;
	size_t	str_len;

	i = 0;
	cnt = 0;
	str_len = 0;
	while (1)
	{
		if (str[i] == '"')
			cnt += plus_pos(str, &i, '"');
		if (str[i] == '\'')
			cnt += plus_pos(str, &i, '\'');
		if ((str[i] == c || str[i] == '\0') && str_len > 0)
			cnt++;
		if (str[i] == '\0')
			break ;
		if (str[i] != c)
			str_len++;
		else
			str_len = 0;
		i++;
	}
	return (cnt);
}

char	**lexer(char *line)
{
	char	**temp;
	size_t	size;

	check_line(line);
	printf("\nsize is %zu\n", count_size(line, ' '));
	size = count_size(line, ' ');
	temp = malloc(size + 1);
	if (temp == NULL)
		return (NULL);
	temp[size] = NULL;
	
	// temp = lx_split(line, ' ');
	return (temp);
}
