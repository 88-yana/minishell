/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:02:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/30 14:57:02 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/minishell.h"

typedef struct s_str
{
	t_type			type;
	char			*str;
	char			**cmd;
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
	{
		new->prev = strlistlast(*lexical_line);
		strlistlast(*lexical_line)->next = new;
	}
}

static bool	is_se(char c)
{
	if (c == ' ')
		return (true);
	if (c == '\0')
		return (true);
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	if (c == '&')
		return (true);
	if (c == '|')
		return (true);
	if (c == '(')
		return (true);
	if (c == ')')
		return (true);
	return (false);
}

static bool	is_dse(char c)
{
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	if (c == '&')
		return (true);
	if (c == '|')
		return (true);
	return (false);
}

static t_str	*make_strlist(char *line, int *i, int *str_len)
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

static t_str	*make_strlistcmd(char **cmd)
{
	t_str	*list;

	list = malloc(sizeof(t_str));
	if (list == NULL)
		return (NULL);
	list->type = CMD;
	list->cmd = cmd;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

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

static bool	is_bracket(const char c)
{
	if (c == '(')
		return (true);
	if (c == ')')
		return (true);
	return (false);
}

static t_str	*make_strlistsep(t_type type)
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

static void cutline(t_str **lexical_line, char *line, int *i, int *str_len)
{
	if (*str_len > 0)
		strlistadd(lexical_line, make_strlist(line, i, str_len)); //2文字系1文字系関わらず
	if (is_dse(line[*i])) //2文字系
	{
		if (line[*i] == line[*i + 1]) //2文字の場合
		{
			strlistadd(lexical_line, make_strlistsep(ctotype(line[*i], 2)));
			(*i)++;
		}
		else if (line[*i] != '&') //1文字の場合
			strlistadd(lexical_line, make_strlistsep(ctotype(line[*i], 1)));
		else
		{
			(*i)++;
			*str_len = 1;
			strlistadd(lexical_line, make_strlist(line, i, str_len));
		}
	}
	else if (is_bracket(line[*i])) //2文字解釈はしないブラケット
		strlistadd(lexical_line, make_strlistsep(ctotype(line[*i], 1)));
	*str_len = -1;
}

static void init_new_lexer(int *i, int *str_len, bool during_[2], t_str **line)
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

static bool is_redirect(t_type type)
{
	if (type == LT)
		return (true);
	if (type == GT)
		return (true);
	if (type == LTLT)
		return (true);
	if (type == GTGT)
		return (true);
	return (false);
}

static bool	str_to_aim(t_str *lexical_line)
{
	while (lexical_line != NULL)
	{
		if (is_redirect(lexical_line->type))
		{
			if (lexical_line->next->type == STR)
				lexical_line->next->type = AIM;
			else
				return (false);
		}
		lexical_line = lexical_line->next;
	}
	return (true);
}

static char	**make_cmd(t_str *start, t_str *last, int cnt)
{
	t_str	*current;
	char	**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * (cnt + 1));
	current = start;
	i = 0;
	while (1)
	{
		cmd[i] = current->str;
		if (current == last)
			break ;
		current = current->next;
		i++;
	}
	cmd[i + 1] = NULL;
	return (cmd);
}

// static void	free_strliststr(t_str *start, t_str *last)
// {
// 	t_str	*temp;

// 	while (1)
// 	{
// 		// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
// 		temp = start->next;
// 		free(start);
// 		if (start == last)
// 			break ;
// 		start = temp;
// 	}
// }

static t_str	*find_start(t_str *head)
{
	while (head->type != STR && head->next != NULL)
		head = head->next;
	return (head);
}

static t_str	*find_last(t_str *head, int *cnt)
{
	while (head->next != NULL && head->next->type == STR)
	{
		head = head->next;
		(*cnt)++;
	}
	return (head);
}

static bool	conv_str_to_cmd(t_str *head)
{
	t_str	*start;
	t_str	*last;
	t_str	*current;
	t_str	*cmdlist;
	int		cnt;
	char	**cmd;

	start = find_start(head);
	if (start->type != STR)
		return (false);
	current = start;
	cnt = 1;
	last = find_last(head, &cnt);
	cmd = make_cmd(start, last, cnt);
	cmdlist = make_strlistcmd(cmd);

	int i = 0;
	while (cmdlist->cmd[i] != NULL)
	{
		printf("cmd %s\n", cmdlist->cmd[i]);
		i++;
	}
	// start = current;
	// cnt = 1;
	// while (current->next != NULL && current->next->type == STR)
	// {
	// 	cnt++;
	// 	current = current->next;
	// }
	// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	// // free_strliststr(start, current);
	// if (start->prev != NULL)
	// 	start->prev->next = cmdlist;
	// else
	// 	start = cmdlist;
	// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	// if (current->prev != NULL)
	// 	current->prev = cmdlist;
	// else
	// 	current->prev = cmdlist;
	// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	return (true);
}

static void	str_to_cmd(t_str *lexical_line)
{
	conv_str_to_cmd(lexical_line);
	printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
}

static /* t_list **/void	reader(char *line)
{
	t_str	*lexical_line;

	lexical_line = new_lexer(line);
	if (!str_to_aim(lexical_line))
	{
		free_strlist(&lexical_line);
		exit (1);
	}
	str_to_cmd(lexical_line);
	printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	while (lexical_line != NULL)
	{
		if (lexical_line->type == STR)
			printf("str is 「%s」\n", lexical_line->str);
		else if (lexical_line->type == AIM)
			printf("aim is 「%s」\n", lexical_line->str);
		else if (lexical_line->type == CMD)
		{
			int i = 0;
			while (lexical_line->cmd[i] != NULL)
			{
				printf("%s\n", lexical_line->cmd[i]);
				i++;
			}
		}
		else
			printf("%d\n", lexical_line->type);
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
