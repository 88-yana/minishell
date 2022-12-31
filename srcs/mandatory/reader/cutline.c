/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:39:21 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 17:35:59 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static t_type	ctotype(const char c, int num)
{
	if (c == '(')
		return (BRA);
	if (c == ')')
		return (CKET);
	if (num == 1)
	{
		if (c == '|')
			return (PIPE);
		if (c == '<')
			return (LT);
		if (c == '>')
			return (GT);
	}
	else if (num == 2)
	{
		if (c == '&')
			return (AND);
		if (c == '|')
			return (OR);
		if (c == '<')
			return (LTLT);
		if (c == '>')
			return (GTGT);
	}
	return (0);
}

static t_str	*make_slistsep(t_type type)
{
	t_str	*list;

	list = malloc(sizeof(t_str));
	if (list == NULL)
		return (NULL);
	list->type = type;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

static t_str	*make_slist(char *line, int *i, int *str_len)
{
	t_str	*list;

	list = malloc(sizeof(t_str));
	if (list == NULL)
		return (NULL);
	list->type = STR;
	list->str = ft_substr(line, *i - *str_len, *str_len);
	if (list->str == NULL)
		return (NULL);
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

void	cutline(t_str **lexical_line, char *line, int *i, int *str_len)
{
	if (*str_len > 0)
		slistadd(lexical_line, make_slist(line, i, str_len));
	if (is_dse(line[*i]))
	{
		if (line[*i] == line[*i + 1])
		{
			slistadd(lexical_line, make_slistsep(ctotype(line[*i], 2)));
			(*i)++;
		}
		else if (line[*i] != '&' && line[*i] != ';')
			slistadd(lexical_line, make_slistsep(ctotype(line[*i], 1)));
		else
		{
			(*i)++;
			*str_len = 1;
			slistadd(lexical_line, make_slist(line, i, str_len));
		}
	}
	else if (is_bracket(line[*i]))
		slistadd(lexical_line, make_slistsep(ctotype(line[*i], 1)));
	*str_len = -1;
}
