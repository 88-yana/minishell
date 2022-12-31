/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:02:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 12:13:01 by hyanagim         ###   ########.fr       */
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

static void	free_slist(t_str *head)
{
	t_str	*temp;
	t_str	*current;

	current = head;
	while (1)
	{
		temp = current->next;
		free(current);
		current = temp;
		if (current == NULL)
			break ;
	}
}

static t_str	*slistlast(t_str *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

static void	slistadd(t_str **head, t_str *new)
{
	if (new == NULL)
	{
		free_slist(*head);
		exit(1);
	}
	if (*head == NULL)
		*head = new;
	else
	{
		new->prev = slistlast(*head);
		slistlast(*head)->next = new;
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
	if (c == ';')
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
	if (c == ';')
		return (true);
	return (false);
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

static t_str	*make_slistcmd(char **cmd)
{
	t_str	*list;

	list = malloc(sizeof(t_str));
	if (list == NULL)
		return (NULL);
	list->type = COMMAND;
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

static void cutline(t_str **lexical_line, char *line, int *i, int *str_len)
{
	if (*str_len > 0)
		slistadd(lexical_line, make_slist(line, i, str_len)); //2文字系1文字系関わらず
	if (is_dse(line[*i])) //2文字系
	{
		if (line[*i] == line[*i + 1]) //2文字の場合
		{
			slistadd(lexical_line, make_slistsep(ctotype(line[*i], 2)));
			(*i)++;
		}
		else if (line[*i] != '&' && line[*i] != ';') //1文字の場合
			slistadd(lexical_line, make_slistsep(ctotype(line[*i], 1)));
		else
		{
			(*i)++;
			*str_len = 1;
			slistadd(lexical_line, make_slist(line, i, str_len));
		}
	}
	else if (is_bracket(line[*i])) //2文字解釈はしないブラケット
		slistadd(lexical_line, make_slistsep(ctotype(line[*i], 1)));
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
	while (i < cnt)
	{
		cmd[i] = current->str;
		if (current == last)
			break ;
		current = current->next;
		i++;
	}
	cmd[cnt] = NULL;
	return (cmd);
}

static void	free_sliststr(t_str *start, t_str *last)
{
	t_str	*temp;
	t_str	*current;

	current = start;
	while (1)
	{
		temp = current->next;
		free(current);
		if (current == last)
			break ;
		current = temp;
	}
}

static t_str	*find_startstr(t_str *head)
{
	while (head->type != STR && head->next != NULL)
		head = head->next;
	return (head);
}

static t_str	*find_laststr(t_str *head, int *cnt)
{
	while (head->next != NULL && head->next->type == STR)
	{
		head = head->next;
		(*cnt)++;
	}
	return (head);
}

static void	connect_cmd(t_str **head, t_str *start, t_str *last, t_str *cmdlist)
{
	if (start->prev)
	{
		start->prev->next = cmdlist;
		cmdlist->prev = start->prev;
		cmdlist->next = last->next;
	}
	else
	{
		*head = cmdlist;
		cmdlist->next = last->next;
	}
	if (last->next)
	{
		last->next->prev = cmdlist;
		cmdlist->prev = start->prev;
		cmdlist->next = last->next;
	}
	free_sliststr(start, last);
}

static bool	conv_str_to_cmd(t_str **head)
{
	t_str	*start;
	t_str	*last;
	t_str	*current;
	t_str	*cmdlist;
	int		cnt;

	start = find_startstr(*head);
	if (start->type != STR)
		return (false);
	current = start;
	cnt = 1;
	last = find_laststr(current, &cnt);
	cmdlist = make_slistcmd(make_cmd(start, last, cnt));
	connect_cmd(head, start, last, cmdlist);
	return (true);
}

static void	str_to_cmd(t_str **lexical_line)
{
	while (1)
	{
		if (conv_str_to_cmd(lexical_line) == false)
			break ;
	}
}

static t_order	*make_order(t_str	*current)
{
	t_order	*order;
	t_type	type;

	type = current->type;
	if (type == COMMAND)
		order = make_command(current->type, current->cmd, NULL, NULL);
	else if (type == GTGT || type == GT || type == LTLT || type == LT)
		order = make_command(current->type, NULL, current->next->str, NULL);
	else
		order = make_command(current->type, NULL, NULL, NULL);
	return (order);
}

static t_list	*ft_lstnewprev(void	*content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		exit(1);
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

static void	ft_lstadd_backprev(t_list **list, t_list *new)
{
		t_list	*last;

	if (new == NULL || list == NULL)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		last = ft_lstlast(*list);
		last->next = new;
		new->prev = last;
	}
}

static t_list	*str_to_list(t_str *head)
{
	t_str	*current;
	t_list	*list;

	list = NULL;
	current = head;
	while (current != NULL)
	{
		ft_lstadd_backprev(&list, ft_lstnewprev(make_order(current))); //FIXME:
		current = current->next;
		if (current != NULL && current->type == AIM)
			current = current->next;
	}
	return (list);
}

static void	swap_list(t_list *list, t_list *next)
{
	t_order	*temp;

	temp = (t_order *)list->content;
	list->content = (t_order *)next->content;
	next->content = temp;
}

static void	sort_red_cmd(t_list *list)
{
	t_order	*current;
	t_order	*next;

	while (list && list->next)
	{
		current = (t_order *)list->content;
		next = (t_order *)list->next->content;
		if (current->type == COMMAND)
			if (is_redirect(next->type))
				swap_list(list, list->next);
		list = list->next;
	}
}

static t_list	*find_bra(t_list *head)
{
	t_list	*current;

	current = ft_lstlast(head);
	while (((t_order *)current->content)->type != BRA && current->prev != NULL)
		current = current->prev;
	return (current);
}

static t_list	*find_cket(t_list *current)
{
	while (((t_order *)current->content)->type != CKET)
		current = current->next;
	return (current);
}

static bool	conv_list_to_subshell(t_list **list)
{
	t_list	*bra;
	t_list	*cket;
	t_list	*current;

	bra = find_bra(*list);
	if (((t_order *)bra->content)->type != BRA)
		return (false);
	current = bra;
	cket = find_cket(current);
	bra->next->prev = NULL;
	cket->prev->next = NULL;
	((t_order *)bra->content)->type = SUBSHELL;
	((t_order *)bra->content)->shell = bra->next;
	bra->next = cket->next;
	if (cket->next)
		cket->next->prev = bra;
	free(cket->content);
	free(cket);
	return (true);
}

static void	list_to_subshell(t_list **list)
{
	while (1)
	{
		if (conv_list_to_subshell(list) == false)
			break ;
	}
}

// static void	print_list(t_list *list)
// {
// 	t_list	*current;

// 	current = list;
// 	while (current != NULL)
// 	{
// 		printf("%d\n", ((t_order *)current->content)->type);
// 		current = current->next;
// 	}
// }


// static void	print_list_r(t_list *list)
// {
// 	t_list	*current;

// 	current = ft_lstlast(list);
// 	while (current != NULL)
// 	{
// 		printf("%d\n", ((t_order *)current->content)->type);
// 		current = current->prev;
// 	}
// }

static t_list	*reader(char *line)
{
	t_str	*lexical_line;
	t_list	*list;

	lexical_line = new_lexer(line);
	if (!str_to_aim(lexical_line)) //aimがない場合
	{
		free_slist(lexical_line);
		exit (1);
	}
	str_to_cmd(&lexical_line);
	list = str_to_list(lexical_line);
	sort_red_cmd(list);
	free_slist(lexical_line);
	// print_list(list);
	// print_list_r(list);
	list_to_subshell(&list);
	display_command(list);

	// system("leaks -q minishell");
	return (list);
}

static void	free_doublechar(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	free_list(t_list *head)
{
	t_list	*temp;
	t_list	*current;

	current = head;
	while (1)
	{
		temp = current->next;
		if (((t_order *)current->content)->type == COMMAND)
			free_doublechar(((t_order *)current->content)->cmd);
		if (is_redirect(((t_order *)current->content)->type))
			free(((t_order *)current->content)->file);
		if (((t_order *)current->content)->type == SUBSHELL)
			free_list(((t_order *)current->content)->shell);
		free(current->content);
		free(current);
		current = temp;
		if (current == NULL)
			break ;
	}
}

static void	minishell(char **envp)
{
	t_vars	vars;

	g_status = 0;
	convert_envp_to_list(&vars, envp);
	while (true)
	{
		vars.line = read_line_from_prompt();
		if (vars.line == NULL)
			continue ;
		vars.comline = reader(vars.line);
		execution(&vars);
		free (vars.line);
		free_list(vars.comline);
		system("leaks -q minishell");
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
// 		// system("leaks -q minishell");
// 		vars.array = lexer(vars.line);
// 		// system("leaks -q minishell");
// 		if (vars.array == NULL)
// 			continue ;
// 		// system("leaks -q minishell");
// 		vars.comline = parser(vars.array);
// 		if (vars.comline == NULL)
// 			continue ;
// 		// system("leaks -q minishell");
// 		execution(&vars);
// 		free_doubleptr(vars.array);
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
