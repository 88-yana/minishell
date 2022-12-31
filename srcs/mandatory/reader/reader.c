/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:08:14 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 19:13:13 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static void	init_new_lexer(int *i, int *str_len, bool during_[2], t_str **line)
{
	*i = -1;
	*str_len = -1;
	during_[DQ] = false;
	during_[SQ] = false;
	*line = NULL;
}

static t_str	*new_lexer(char *line)
{
	int		i;
	int		str_len;
	bool	during_[2];
	t_str	*lexical_line;

	init_new_lexer(&i, &str_len, during_, &lexical_line);
	while (1)
	{
		i++;
		str_len++;
		if (line[i] == DOUBLEQ)
			during_[DQ] = !during_[DQ];
		if (line[i] == SINGLEQ)
			during_[SQ] = !during_[SQ];
		if (during_[DQ] || during_[SQ])
			continue ;
		if (is_se(line[i]))
			cutline(&lexical_line, line, &i, &str_len);
		if (line[i] == '\0')
			break ;
	}
	return (lexical_line);
}

t_list	*reader(char *line)
{
	t_str	*lexical_line;
	t_list	*list;

	if (check_line(line) == false)
	{
		free(line);
		return (NULL);
	}
	lexical_line = new_lexer(line);
	if (!str_to_aim(lexical_line))
	{
		printf("syntax error near unexpected token\n");
		free(line);
		free_slistall(lexical_line);
		return (NULL);
	}
	str_to_cmd(&lexical_line);
	list = str_to_list(lexical_line);
	sort_red_cmd(list);
	free_slist(lexical_line);
	list_to_subshell(&list);
	if (!sort_shell_cmd(list))
	{
		free(line);
		free_list(list);
		return (NULL);
	}
	free(line);
	return (list);
}
