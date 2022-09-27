// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parser.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/25 11:00:40 by hyanagim          #+#    #+#             */
// /*   Updated: 2022/09/26 14:05:35 by hyanagim         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../main/minishell.h"
#define ARRAY_SIZE 14
t_node	*talloc(t_type type, t_node *parent);

t_order	*make_command(t_type type, char **cmd, char *file, t_list *shell)
{
	t_order	*command_line;

	command_line = malloc(sizeof(t_order));
	command_line->type = type;
	if (type == COMMAND)
		command_line->cmd = cmd;
	else
		command_line->cmd = NULL;
	if (type == GTGT || type == GT || type == LTLT || type == LT)
		command_line->file = file;
	else
		command_line->file = NULL;
	command_line->read_fd = -1;
	command_line->write_fd = -1;
	command_line->next_read_fd = -1;
	if (type == SUBSHELL)
		command_line->shell = shell;
	else
		command_line->shell = NULL;
	return (command_line);
}

bool	is_delimiter(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "&&") == 0)
		return (true);
	if (ft_strcmp(str, "||") == 0)
		return (true);
	return (false);
}

bool	is_bra(char c)
{
	if (c == '(')
		return (true);
	return (false);
}

bool	is_pipe(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "|") == 0)
		return (true);
	return (false);
}

bool	is_redirection(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "<") == 0)
		return (true);
	if (ft_strcmp(str, ">") == 0)
		return (true);
	if (ft_strcmp(str, ">>") == 0)
		return (true);
	if (ft_strcmp(str, "<<") == 0)
		return (true);
	return (false);
}

void	parser(t_node *p)
{
	if (p->type == COMMAND_LINE)
	{
// 		if (かっこがあったら，
// 		{
// 			// p->left
// 			// p->type = コマンドライン
// 			if (かっこの終わりがなければ，
// 				error
// 			かっこの終わりまで，エンドポスを進める。
// 			if (デリミターだったら)
// 			{
// 				p->left
// 					デリミター
// 			}
// 			if (パイプだったら)
// 				p->left
// 					パイプドライン
			
// 		}
		// かっこやデリミターが見つかるまで，エンドポスを進める。

		while (p->line[p->end_pos] != NULL &&
			!is_delimiter(p->line[p->end_pos]) && !is_bra(p->line[p->end_pos][0]))
			p->end_pos++;
		// printf("command line is %s\n", p->line[p->end_pos]);
// 		if (かっこだったら)
// 		{
// 			p->left
// 				パイプドライン
// 		}
// 		if (デリミターだったら，)
// 		{
// 			p->left
// 					デリミター

// 			p->right
// 			p->type = コマンドライン
// 		}
// 		if (NULLだったら，全体がパイプドラインだから，)
// 		{
// 			p->left
// 			p->type = パイプドライン
// 		}
		if (p->line[p->end_pos] == NULL)
		{
			// printf("before piped line command line is start %s\n", p->line[p->start_pos]);
			// printf("before piped line command line is end %s\n", p->line[p->end_pos]);
			p->end_pos = p->start_pos;
			p->left = talloc(PIPED_LINE, p);
			parser(p->left);
		}
	}
	if (p->type == PIPED_LINE)
	{
		while (p->line[p->end_pos] != NULL && !is_delimiter(p->line[p->end_pos]) && !is_bra(p->line[p->end_pos][0]) &&
			!is_pipe(p->line[p->end_pos]))
			p->end_pos++;
		// printf("piled_line %s\n", p->line[p->end_pos]);
		if (is_pipe(p->line[p->end_pos]))
		{
			p->current_pos = p->end_pos;
			p->end_pos = p->start_pos;
			// printf("before piped piped line is start %s\n", p->line[p->start_pos]);
			// printf("before piped piped line is end %s\n", p->line[p->end_pos]);
			p->left = talloc(PIPE, p);
			parser(p->left);
		}
		if (p->line[p->end_pos] == NULL)
		{
			p->end_pos = p->start_pos;
			// printf("before arguments piped line is start %s\n", p->line[p->start_pos]);
			// printf("before arguments piped line is end %s\n", p->line[p->end_pos]);
			p->left = talloc(ARGUMENTS, p);
			parser(p->left);
		}
	}
	if (p->type == PIPE)
	{
		// printf("pipe is %s\n", p->line[p->current_pos]);
		// printf("before arguments pipe is start %s\n", p->line[p->start_pos]);
			// printf("before arguments pipe is end %s\n", p->line[p->end_pos]);
		p->left = talloc(ARGUMENTS, p);
		parser(p->left);
		p->start_pos = p->current_pos + 1;
		p->end_pos = p->current_pos + 1;
		p->include_right = true;
		p->right = talloc(PIPED_LINE, p);
		parser(p->right);
	}
	// if (p->type == COMMAND)
	// {
	// 	// printf("command is %s\n", p->line[p->end_pos]);
	// 	p->left = talloc(ARGUMENTS, p);
	// 	parser(p->left);
	// }
	if (p->type == ARGUMENTS)
	{
		//間違っている
		// printf("argument is %s\n", p->line[p->end_pos]);
		if (is_redirection(p->line[p->end_pos]))
		{
			p->left = talloc(REDIRECTION, p);
			parser(p->left);
			p->end_pos++;
			if (p->line[p->end_pos] == NULL)
				return ;
			p->end_pos++;
			if (p->line[p->end_pos] != NULL)
			{
				p->start_pos = p->end_pos;
				p->include_right = true;
				p->right = talloc(ARGUMENTS, p);
				parser(p->right);
			}
		}
		else
		{
			while (p->line[p->end_pos] != NULL && !is_delimiter(p->line[p->end_pos]) &&
				!is_bra(p->line[p->end_pos][0]) && !is_pipe(p->line[p->end_pos]) && !is_redirection(p->line[p->end_pos]))
			p->end_pos++;
			if (is_redirection(p->line[p->end_pos]))
			{
				// if (p->end_pos == p->start_pos) //後で消すかも
				// 	return ;
				// printf("171 %s\n", p->line[p->end_pos]);
				p->current_pos = p->end_pos;
				p->end_pos = p->start_pos;
				p->left = talloc(COMMAND, p);
				parser(p->left);
				p->start_pos =	p->current_pos;
				p->end_pos = p->current_pos;
				p->include_right = true;
				p->right = talloc(ARGUMENTS, p);
				parser(p->right);
			}
			else
			{
				p->end_pos = p->start_pos;
				p->left = talloc(COMMAND, p);
				parser(p->left);
			}
		}
		
		// p->start_pos = p->end_pos;
		
		// else
		// {
		// 	if (p->line[p->start_pos] == NULL)
		// 		return ;
		// 	p->end_pos = p->start_pos;
		// 	printf("184 %s\n", p->line[p->end_pos]);
		// 	p->left = talloc(COMMAND, p);
		// }
	}
	if (p->type == REDIRECTION)
	{
		p->current_pos = p->end_pos; //redirection
		// printf("redirecition is %s, including right is %d\n", p->line[p->end_pos], p->include_right);
		p->end_pos++;
		if (p->line[p->end_pos] == NULL)
		{
			// printf("%s\n", "error in redirection");
			return ;
			//ここで，free
		}
		// printf("aim is %s\n", p->line[p->end_pos]);
		// p->end_pos++;
		// if (p->line[p->end_pos] != NULL)
		// {
		// 	p->start_pos = p->current_pos + 2;
		// 	p->end_pos = p->current_pos + 2;
		// 	// printf("204 %s\n", p->line[p->end_pos]);
		// 	p->right = talloc(COMMAND, p);
		// 	parser(p->right);
		// }
	}
	if (p->type == COMMAND)
	{
		// printf("string start %s\n", p->line[p->start_pos]);
		// printf("string end %s\n", p->line[p->end_pos]);
		// printf("string is %s\n", p->line[p->end_pos]);
		/* p->left = talloc(EXPANDABLE, p);
		parser(p->left);
		p->end_pos++;
		if (p->line[p->end_pos] != NULL && !is_delimiter(p->line[p->end_pos]) && !is_bra(p->line[p->end_pos][0])
			&& !is_pipe(p->line[p->end_pos]) && !is_redirection(p->line[p->end_pos]))
		{
			// printf("「string is in if %s」\n", p->line[p->end_pos]);
			p->start_pos = p->end_pos;
			p->include_right = true;
			p->right = talloc(EXPANDABLE, p);
			parser(p->right);
		} */
		return ;
	}
	if (p->type == EXPANDABLE)
	{
		// printf("expandable is %s, including right is %d\n", p->line[p->end_pos], p->include_right);
	}
	return ;
}

//""を外した先頭のexpandableコマンドが全部アルファベットだったら，外していい
// リダイレクションとサブシェルの位置関係はいじれない


t_node	*talloc(t_type type, t_node *parent)
{
	t_node *p;
	p = malloc(sizeof(t_node));
	p->type = type;
	p->line = parent->line;
	p->ele_is_quoted = parent->ele_is_quoted;
	p->ele_length = parent->ele_length;
	p->array_size = parent->array_size;
	p->start_pos = parent->start_pos;
	p->current_pos = parent->current_pos; //?????後で見る。
	p->end_pos = parent->end_pos;
	p->include_right = parent->include_right;
	p->index = parent->index + 1;
	p->parent =  parent;
	p->left = parent->left;
	p->right = parent->right;
	// node自体と，コマンドラインの分のmallocをする。
	// typeの代入と，コマンドのポインタの代入をする？（ポインタの複製。）
	// スタートポスとエンドポスの初期化をする。
	// 最初と最後は最初は一緒。
	return p;
}
// //talloc 失敗した時のエラー処理を後で書く

t_list **realloc_list(t_list **list, t_list *ptr)
{
	t_list	**new;
	size_t	size;
	size_t	i;

	size = 0;
	while (list[size] != NULL)
		size++;
	new = malloc(sizeof(t_list *) * (size + 2));
	i = 0;
	while (i < size)
	{
		new[i] = list[i];
		i++;
	}
	
	new[size] = ptr;
	new[size + 1] = NULL;
	// free(list);
	return (new);
}

t_type	convert_redirection(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (LT);
	if (ft_strcmp(str, ">") == 0)
		return (GT);
	if (ft_strcmp(str, ">>") == 0)
		return (GTGT);
	if (ft_strcmp(str, "<<") == 0)
		return (LTLT);
	return (COMMAND_LINE);
}

size_t	test(t_list **list)
{
	size_t i = 0;
	while (list[i] != NULL)
	{
		if (i == 2)
		{
			i++;
			continue;
		}
		printf("list point %p\n", list[i]);
		printf("list type %u\n", ((t_order *)list[i]->content)->type);
		if (((t_order *)list[i]->content)->type == COMMAND)
			printf("list cmd in comma %s\n", ((t_order *)list[i]->content)->cmd[0]);
		i++;
		printf("\n");
	}
	return (i);
}

void size_index(t_list **list, t_node *p, t_type type)
{
	int i = 0;
	while (list[i] != NULL)
		i++;
	if (type == COMMAND)
		printf("in command %d\n", i);
	if (type == ARGUMENTS)
		printf("in arguments %d\n", i);
	if (type == REDIRECTION)
		printf("in  %d\n", i);
	printf("index is %zu\n\n", p->index);
}

size_t listlen(t_list **list)
{
	size_t	i;

	i = 0;
	while (list[i] != NULL)
		i++;
	return (i);
}

t_list	**listjoin(t_list **list, t_list **latter)
{
	size_t	length;
	size_t	i;
	size_t	j;
	t_list	**new;

	length = listlen(list) + listlen(latter) + 1;
	new = malloc(sizeof(t_list * ) * length);
	i = 0;
	while (list[i] != NULL)
	{
		new[i] = list[i];
		i++;
	}
	j = 0;
	while (latter[j] != NULL)
	{
		new[i + j] = latter[j];
		j++;
	}
	new[length] = NULL;
	return (new);
}

static void	comswap(t_list **list, size_t i, size_t j)
{
	t_list *temp;

	if (((t_order *)list[i]->content)->type > ((t_order *)list[j]->content)->type)
	{
		temp = list[i];
		list[i] = list[j];
		list[j] = temp;
	}
}

t_list	**sort_list(t_list	**list)
{
	size_t	i;
	size_t	j;

	i = listlen(list);
	while (i > 1)
	{	
		j = 0;
		while (j < i - 1)
		{
			comswap(list, j, j + 1);
			j++;
		}
		i--;
	}
	return (list);
}


t_list	**executer(t_node *p, t_list **list)
{
	if (p->type == COMMAND_LINE)
		list = executer(p->left, list);
/* 	if (p->type == DELIMITER)
	{
		executer(p->left, list);
		executer(p->right, list);
	}
	if (p->type == subshell)
	{
		t_list	*shell;
		t_list	*command_line;
		exe(p->left, shell);

		command_line = ft_lstnew(make_command(SHELL, (char *[]){"/bin/ls", NULL}, NULL, shell));
	} */
	if (p->type == PIPED_LINE)
		list = executer(p->left, list);

	if (p->type == PIPE)
	{
		t_list	**latter;
		latter = malloc(sizeof(t_list *));
		latter[0] = NULL;
		t_list	*list_ptr;
		list_ptr = ft_lstnew(make_command(PIPE, NULL, NULL, NULL));
		list = executer(p->left, list);
		list = realloc_list(list, list_ptr);
	
		latter = malloc(sizeof(t_list *) * 1);
		latter[0] = NULL;
		latter = executer(p->right, latter);
		list = listjoin(list, latter);
	}
	if (p->type == ARGUMENTS)
	{
		list = executer(p->left, list);
		if (p->right != NULL)
			list = executer(p->right, list);
		if (p->parent->type == PIPE)
		{
			list = sort_list(list);
		}
		if (p->parent->type == PIPED_LINE)
		{
			list = sort_list(list);
		}
	}
	if (p->type == REDIRECTION)
	{
		t_list	*list_ptr;
		t_type	type;
		type = convert_redirection(p->line[p->current_pos]);
		list_ptr = ft_lstnew(make_command(type, NULL, p->line[p->current_pos + 1], NULL));
		list = realloc_list(list, list_ptr);
		/* int i = 0;
		while (list[i] != NULL && size  == 2)
		{
			printf("list point in comma %p\n", list[i]);
			printf("list type in comma %u\n", ((t_order *)list[i]->content)->type);
			if (((t_order *)list[i]->content)->type == COMMAND)
				printf("list cmd in comma %s\n", ((t_order *)list[i]->content)->cmd[0]);
			i++;
		} */
	}
	if (p->type == COMMAND)
	{
		char	**array;
		int		i;
		t_list	*list_ptr;
		while (p->line[p->end_pos] != NULL && !is_delimiter(p->line[p->end_pos]) && !is_bra(p->line[p->end_pos][0])
			&& !is_pipe(p->line[p->end_pos]) && !is_redirection(p->line[p->end_pos]))
			p->end_pos++;
		array = malloc(sizeof(char *) * (p->end_pos - p->start_pos + 1));
		if (array == NULL)
			; //後で書く。
		i = 0;
		while (i < p->end_pos - p->start_pos)
		{
			array[i] = ft_strdup(p->line[p->start_pos + i]);
			if (array[i] == NULL)
				; //後で書く。
			i++;
		}
		array[i] = NULL;
		list_ptr = ft_lstnew(make_command(COMMAND, array, NULL, NULL));
		list = realloc_list(list, list_ptr);
		// size_index(list, p, COMMAND);
	}
	return (list);
}
// //stringかなんかで，
// //p->left が NULL だったら，lstnew して，登りながら，lstadd していく。


void	display_command(t_list *command_line)
{
	size_t	i;
	t_list	*buf;
	t_order	*command;

	buf = command_line;
	while (buf)
	{
		command = (t_order *)buf->content;
		if (command->type == COMMAND)
		{
			printf("type: [ %s ] command: [", "command");
			i = 0;
			while (command->cmd[i])
			{
				printf(" %s", command->cmd[i]);
				i++;
			}
			printf(" ]\n");
		}
		else if (command->type == SUBSHELL)
		{
			printf("type: [ %s ]\n", "shell");
			printf("---------- inside shell ----------\n");
			display_command(command->shell);
		}
		else if (command->type == GT)
		{
			printf("type: [ %s ]", "gt");
			printf(" aim: [ %s ]\n", command->file);
		}
		else if (command->type == PIPE)
			printf("type: [ %s ]\n", "pipe");
		else if (command->type == AND)
			printf("type: [ %s ]\n", "and");
		else if (command->type == OR)
			printf("type: [ %s ]\n", "or");
		buf = buf->next;
	}
}

void	listlcpy(t_list **dst, t_list **list, size_t dstsize)
{
	size_t	i;

	if (dstsize > 0)
	{
		i = 0;
		while (list[i] && i < dstsize - 1)
		{
			dst[i] = list[i];
			i++;
		}
		dst[i] = NULL;
	}
}

size_t	arraylen(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void	display_array(char ** arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

char	**arrayjoin(char **arr1, char**arr2)
{
	size_t	length;
	size_t	i;
	size_t	j;
	char	**new;

	length = arraylen(arr1) + arraylen(arr2) + 1;
	new = malloc(sizeof(char * ) * length);
	i = 0;
	while (arr1[i] != NULL)
	{
		new[i] = arr1[i];
		i++;
	}
	j = 0;
	while (arr2[j] != NULL)
	{
		new[i + j] = arr2[j];
		j++;
	}
	new[length] = NULL;
	i = 0;
	return (new);
}


void	cmdjoin(t_list **list)
{
	size_t i;

	i = 0;
	while (i < listlen(list) - 1)
	{
		if (((t_order *)list[i]->content)->type == COMMAND &&
			((t_order *)list[i + 1]->content)->type == COMMAND)
		{
			((t_order *)list[i]->content)->cmd = arrayjoin(((t_order *)list[i]->content)->cmd, ((t_order *)list[i + 1]->content)->cmd);
			listlcpy(&(list[i + 1]), &(list[i + 2]), listlen(list));
		}
		i++;
	}
}

void	init_root(t_node *root)
{
	root->array_size = 11;
	root->start_pos = 0;
	root->current_pos = 0;
	root->end_pos = 0;
	root->include_right = 0;
	root->index = 0;
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
}

int	main(void)
{
	t_node	root;
	t_node	**wood;
	t_list	**list;
	t_list	**maked_list;
	char	**line;
	char	**array;
	t_array	data;

	line = malloc(sizeof(char *) * (ARRAY_SIZE + 1));
	for (int i = 0; i < ARRAY_SIZE + 1; i++)
		line[i] = malloc(sizeof(char) * 10);

	line[0] = "echo";
	line[1] = "hello";
	line[2] = ">";
	line[3] = "text.txt";
	line[4] = "world";
	line[5] = "|";
	line[6] = "echo";
	line[7] = "abc";
	line[8] = "def";
	line[9] = ">";
	line[10] = "text01.txt";
	line[11] = "|";
	line[12] = "grep";
	line[13] = "a";
	line[14] = NULL;
	// line[0] = "echo";
	// line[1] = "hello";
	// line[2] = ">";
	// line[3] = "text.txt";
	// line[4] = "world";
	// line[5] = "|";
	// line[6] = "echo";
	// line[7] = "abc";
	// line[8] = "|";
	// line[9] = "grep";
	// line[10] = "a";
	// line[11] = NULL;
	// data.line = ;
	// array = lexer(&data);
	root.line = line;
	root.type = COMMAND_LINE;
	init_root(&root);
	
	for (int i = 0; i < ARRAY_SIZE + 1; i++)
		printf("%s ", line[i]);
	printf("\n");
	parser(&root);
	wood = malloc(sizeof(t_node *) * 2);
	wood[0] = &root;
	wood[1] = NULL;
	// printf("wood is %s\n", wood[0]->line[0]);
	// printf("wood is %p\n", wood[1]);
	/*
	list = malloc(sizeof(t_list *) * 2);
	list[0] = ft_lstnew(make_command(COMMAND, root.line, NULL, NULL));
	list[1] = NULL;
	printf("%p\n", list[0]);
	printf("%d\n", ((t_order *)list[0]->content)->type);
	*/
	list = malloc(sizeof(t_list *) * 1);
	list[0] = NULL;
	// printf("point is %p\n", list[0]);
	// printf("content point is %p\n", list[0]->content);
	// printf("%p\n", list);
	list = executer(&root, list);
	int i = 0;
	// t_list	*list_ptr = ft_lstnew(make_command(COMMAND, root.line, NULL, NULL));
	// list = realloc_list(list, list_ptr);
	while (list[i] != NULL)
	{
		// printf("main %s\n", ((t_order *)list[i]->content)->cmd[0]);
		// printf("main %d, %u\n", i, ((t_order *)list[i]->content)->type);
		// int j = 0;
		// while (((t_order *)list[i]->content)->type == COMMAND && ((t_order *)list[i]->content)->cmd[j] != NULL)
		// {
		// 	printf(" %s\n", ((t_order *)list[i]->content)->cmd[j]);
		// 	j++;
		// }	
		i++;
	}
	cmdjoin(list);
	*maked_list = NULL;
	i = 0;
	while (list[i] != NULL)
	{
		ft_lstadd_back(maked_list, list[i]);
		i++;
	}
	display_command(*maked_list);
	return (0);
}

/*
command_line ::=
	| "(" command_line ")" delimiter command_line
	| "(" command_line ")" "|" command_line
	| "(" command_line ")" re
	| piped_commands delimiter command_line
	| piped_commands "|" "(" command_line ")"
	| piped_commands

パイプの後にかっこがある場合がある。
piped_commands | (command_line) 的な
↑これもパイプライン？　no
"(" command_line ")" > text.txt ←これも存在する。

delimiter ::=
	"&&"
	"||"

piped_commands ::=
	| command "|" piped_commands
	
	| command

command ::=
	| arguments

arguments ::=
	| redirection
	| redirection arguments
	| string
	| string arguments

string ::=
	| expandable <no_space> string
	| expandable
	| not_expandable <no_space> string
	| not_expandable
	| expandable_quoted <no_space> string
	| expandable_quoted

redirection ::=
	| "<" aim
	| ">" aim
	| ">>" aim
	| "<<" aim
	| "<"aim //後でやる。
	| ">"aim //後でやる。
	| ">>"aim //
	| "<<"aim //
*/

/*
command_line ::=
	| "(" command_line ")" delimiter command_line
	| "(" command_line ")" "|" command_line
	| "(" command_line ")" redirection
	| "(" command_line ")" redirection delimiter command_line
	| "(" command_line ")" redirection "|" command_line
	| piped_commands delimiter command_line
	| piped_commands "|" "(" command_line ")"
	| piped_commands

パイプの後にかっこがある場合がある。
piped_commands | (command_line) 的な
↑これもパイプライン？　no


delimiter ::=
	"&&"
	"||"

piped_commands ::=
	| command "|" piped_commands
	
	| command

arguments ::=
	| redirection
	| redirection arguments
	| command
	| command arguments

command ::=
	| expandable <no_space> command
	| expandable
	| not_expandable <no_space> command
	| not_expandable
	| expandable_quoted <no_space> command
	| expandable_quoted

redirection ::=
	| "<" command
	| ">" command
	| ">>" command
	| "<<" command
*/