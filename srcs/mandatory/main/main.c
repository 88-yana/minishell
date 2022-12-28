/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:02:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/28 21:28:15 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/minishell.h"

typedef struct s_str
{
	t_type			type;
	char			*cmd;
	struct s_str	*next;
	struct s_str	*prev;
}	t_str;

//TODO:
static void	free_strlist(t_str **lexical_line)
{
	(void) lexical_line;
	return ;
}

static t_str	*strlistlast(t_str *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

static void	strlistadd(t_str **lexical_line, t_str *new)
{
	if (new == NULL)
	{
		free_strlist(lexical_line);
		exit(1);
	}
	if (*lexical_line == NULL)
		*lexical_line = new;
	else
		strlistlast(*lexical_line)->next = new;
}

static bool	is_se(char c)
{
	if (c == ' ')
		return (true);
	if (c == '\0')
		return (true);
	return (false);
}

static t_str	*make_strlist(char *line, int *i, int *str_len)
{
	t_str	*strlist;

	strlist = malloc(sizeof(t_str));
	if (strlist == NULL)
		return (NULL);
	strlist->next = NULL;
	strlist->prev = NULL;
	strlist->cmd = ft_substr(line, *i - *str_len, *str_len);
	return (strlist);
}

static void cutline(t_str **lexical_line, char *line, int *i, int *str_len)
{
	if (*str_len > 0)
		if (line[*i] == '&') //2文字系
			;
		else //一文字系
			strlistadd(lexical_line, make_strlist(line, i, str_len));
	*str_len = -1;
}

static t_str	*new_lexer(char *line)
{
	int		i;
	int		str_len;
	bool	during_dq;
	bool	during_sq;
	t_str	*lexical_line;

	i = -1;
	str_len = -1;
	during_dq = false;
	during_sq = false;
	lexical_line = NULL;
	while (1)
	{
		i++;
		str_len++;
		if (line[i] == DOUBLEQ)
			during_dq = !during_dq;
		if (line[i] == SINGLEQ)
			during_sq = !during_sq;
		if (during_dq || during_sq)
			continue ;
		if (is_se(line[i]))
			cutline(&lexical_line, line, &i, &str_len);
		if (line[i] == '\0')
			break ;
	}
	return (lexical_line);
}

static /* t_list **/void	reader(char *line)
{
	t_str	*lexical_line;

	lexical_line = new_lexer(line);
	while (lexical_line != NULL)
	{
		printf("cmd is 「%s」\n", lexical_line->cmd);
		lexical_line = lexical_line->next;
	}
	return ;
}

static void	minishell(char **envp)
{
	char	*line;

	(void)envp;
	while (true)
	{
		line = read_line_from_prompt();
		if (line == NULL)
			continue ;
		reader(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}

// #include	"../../../includes/minishell.h"

// static void	minishell(char **envp)
// {
// 	t_vars	vars;

// 	g_status = 0;
// 	convert_envp_to_list(&vars, envp);
// 	while (true)
// 	{
// 		vars.line = read_line_from_prompt();
// 		if (vars.line == NULL)
// 			continue ;
// 		// system("leaks -q minishell");
// 		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
// 		// system("leaks -q minishell");
// 		vars.array = lexer(vars.line);
// 		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
// 		// system("leaks -q minishell");
// 		if (vars.array == NULL)
// 			continue ;
// 		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
// 		// system("leaks -q minishell");
// 		vars.comline = parser(vars.array);
// 		if (vars.comline == NULL)
// 			continue ;
// 		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
// 		// system("leaks -q minishell");
// 		execution(&vars);
// 		free_doubleptr(vars.array);
// 		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
// 		// system("leaks -q minishell");
// 		ft_lstclear(&(vars.comline), free);
// 		free(vars.line);
// 		// system("leaks -q minishell");
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	minishell(envp);
// 	return (0);
// }
