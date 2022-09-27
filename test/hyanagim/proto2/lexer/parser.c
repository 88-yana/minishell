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
#define ARRAY_SIZE 11
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
		printf("command line is %s\n", p->line[p->end_pos]);
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
			printf("before piped line command line is start %s\n", p->line[p->start_pos]);
			printf("before piped line command line is end %s\n", p->line[p->end_pos]);
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
			printf("before piped piped line is start %s\n", p->line[p->start_pos]);
			printf("before piped piped line is end %s\n", p->line[p->end_pos]);
			p->left = talloc(PIPE, p);
			parser(p->left);
		}
		if (p->line[p->end_pos] == NULL)
		{
			p->end_pos = p->start_pos;
			printf("before arguments piped line is start %s\n", p->line[p->start_pos]);
			printf("before arguments piped line is end %s\n", p->line[p->end_pos]);
			p->left = talloc(ARGUMENTS, p);
			parser(p->left);
		}
	}
	if (p->type == PIPE)
	{
		printf("pipe is %s\n", p->line[p->current_pos]);
		printf("before arguments pipe is start %s\n", p->line[p->start_pos]);
			printf("before arguments pipe is end %s\n", p->line[p->end_pos]);
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
		printf("redirecition is %s, including right is %d\n", p->line[p->end_pos], p->include_right);
		p->end_pos++;
		if (p->line[p->end_pos] == NULL)
		{
			printf("%s\n", "error in redirection");
			return ;
			//ここで，free
		}
		printf("aim is %s\n", p->line[p->end_pos]);
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
		printf("string start %s\n", p->line[p->start_pos]);
		printf("string end %s\n", p->line[p->end_pos]);
		// printf("string is %s\n", p->line[p->end_pos]);
		p->left = talloc(EXPANDABLE, p);
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
		}
		return ;
	}
	if (p->type == EXPANDABLE)
	{
		printf("expandable is %s, including right is %d\n", p->line[p->end_pos], p->include_right);
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
	size_t	i;

	i = 0;
	new = malloc(sizeof(list) / sizeof(t_list *) + 1);
	while (i < sizeof(list) / sizeof(t_list *) - 1)
	{
		new[i] = list[i];
		i++;
	}
	new[i] = ptr;
	new[i + 1] = NULL;
	printf("exc %p\n", list);
	// free(list);
	return (new);
}

void	executer(t_node *p, t_node **wood)
{
	if (p->type == COMMAND_LINE)
	{
		executer(p->left, wood);
	}
// 	if (p->type == DELIMITER)
// 	{
// 		executer(p->left, wood);
// 		executer(p->right, wood);
// 	}
// 	if (p->type == subshell)
// 	{
// 		t_list	*shell;
// 		t_list	*command_line;
// 		exe(p->left, shell);

// 		command_line = ft_lstnew(make_command(SHELL, (char *[]){"/bin/ls", NULL}, NULL, shell));
// 	}
	if (p->type == PIPED_LINE)
	{
		executer(p->left, wood);
	}
	if (p->type == PIPE)
	{
		t_list	**latter;
		executer(p->left, wood);
		// add_list(list, PIPE);
		// executer(p->left, latter);
		// listjoin(list, latter);
	}
	if (p->type == ARGUMENTS)
	{
		executer(p->left, wood);
		if (p->right != NULL)
			executer(p->right, wood);
	}
	if (p->type == STRING)
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
		while (i < p->end_pos - p->start_pos + 1)
		{
			array[i] = ft_strdup(p->line[p->start_pos + i]);
			if (array[i] == NULL)
				; //後で書く。
			i++;
		}
		
		// list_ptr = ft_lstnew(make_command(COMMAND, (char *[]){"ls", "-l", NULL}, NULL, NULL));
		// t_list *ft_lstnew(void *content)
		// printf("exc %p\n", wood);
		// realloc_list(list, list_ptr);
		i = 0;
		// while (list[i] != NULL)
		// {
			// printf("%s\n", list[i]->content->line[list[i]->content->end_pos]);
		// 	i++;
		// }
		
		// ft_lstadd_back(list, list_ptr);
	}
	// return (wood);
}
// //stringかなんかで，
// //p->left が NULL だったら，lstnew して，登りながら，lstadd していく。


int	main(void)
{
	t_node	root;
	t_node	**wood;
	t_list	**list;
	char	**line;

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
	line[8] = "|";
	line[9] = "grep";
	line[10] = "a";
	line[11] = NULL;
	root.type = COMMAND_LINE;
	root.line = line;
	root.array_size = 11;
	root.start_pos = 0;
	root.current_pos = 0;
	root.end_pos = 0;
	root.include_right = 0;
	root.parent = NULL;
	root.left = NULL;
	root.right = NULL;
	for (int i = 0; i < ARRAY_SIZE + 1; i++)
		printf("%s ", line[i]);
	printf("\n");
	parser(&root);
	wood = malloc(sizeof(t_node *) * 2);
	wood[0] = &root;
	wood[1] = NULL;
	printf("wood is %s\n", wood[0]->line[0]);
	printf("wood is %p\n", wood[1]);
	/*
	list = malloc(sizeof(t_list *) * 2);
	list[0] = ft_lstnew(make_command(COMMAND, root.line, NULL, NULL));
	list[1] = NULL;
	printf("%p\n", list[0]);
	printf("%d\n", ((t_order *)list[0]->content)->type);
	printf("%s\n", ((t_order *)list[0]->content)->cmd[0]);
	*/
	// printf("point is %p\n", list[0]);
	// printf("content point is %p\n", list[0]->content);
	// printf("%p\n", list);
	// executer(&root, wood);
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