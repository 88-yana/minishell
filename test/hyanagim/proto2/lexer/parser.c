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
			p->end_pos = p->start_pos;
			p->left = talloc(PIPED_LINE, p);
			parser(p->left);
		}
	}
	if (p->type == PIPED_LINE)
	{
		printf("piled_line %s\n", p->line[p->end_pos]);
		while (p->line[p->end_pos] != NULL &&
			!is_pipe(p->line[p->end_pos]))
			p->end_pos++;
		// printf("piled_line %s\n", p->line[p->end_pos]);
		if (is_pipe(p->line[p->end_pos]))
		{
			p->current_pos = p->end_pos;
			p->end_pos = p->start_pos;
			p->left = talloc(PIPE, p);
			parser(p->left);
		}
		if (p->line[p->end_pos] == NULL)
		{
			p->end_pos = p->start_pos;
			p->left = talloc(COMMAND, p);
			parser(p->left);
		}
	}
	if (p->type == PIPE)
	{
		printf("pipe is %s\n", p->line[p->current_pos]);
		p->left = talloc(COMMAND, p);
		parser(p->left);
		p->start_pos = p->current_pos + 1;
		p->end_pos = p->current_pos + 1;
		p->include_right = true;
		p->right = talloc(PIPED_LINE, p);
		parser(p->right);
	}
	if (p->type == COMMAND)
	{
		printf("command is %s\n", p->line[p->end_pos]);
		p->left = talloc(ARGUMENTS, p);
		parser(p->left);
	}
	if (p->type == ARGUMENTS)
	{
		printf("argument is %s\n", p->line[p->end_pos]);
		if (is_redirection(p->line[p->end_pos]))
		{
			p->left = talloc(REDIRECTION, p);
			parser(p->left);
		}
		p->end_pos++;
		if (p->line[p->end_pos] == NULL)
		{
			printf("%s\n", "error in redirection");
			return ;
		}
		p->end_pos++;
		while (p->line[p->end_pos] != NULL &&
			!is_redirection(p->line[p->end_pos]))
			p->end_pos++;
		
		if (is_redirection(p->line[p->end_pos]))
		{
			p->left = talloc(STRING, p);
			parser(p->left);
			p->start_pos = p->end_pos;
			p->include_right = true;
			p->right = talloc(ARGUMENTS, p);
			parser(p->right);
		}
		else
		{
			if (p->line[p->start_pos] == NULL)
				return ;
			p->end_pos = p->start_pos;
			p->left = talloc(STRING, p);
		}
	}
	if (p->type == REDIRECTION)
	{
		p->current_pos = p->end_pos; //redirection
		printf("redirecition is %s\n", p->line[p->current_pos]);
		p->end_pos++;
		if (p->line[p->end_pos] == NULL)
		{
			printf("%s\n", "error in redirection");
			return ;
			//ここで，free
		}
		p->end_pos++;
		if (p->line[p->end_pos] != NULL)
		{
			p->start_pos = p->current_pos + 2;
			p->end_pos = p->current_pos + 2;
			p->right = talloc(STRING, p);
			parser(p->right);
		}
	}
	// if (p->type == STRING)
	// {
	// 	p->left = talloc(EXPANDABLE, p);
	// 	parser(p->left);
	// 	p->end_pos++;
	// 	if (p->line[p->end_pos] != NULL && !is_delimiter(p->line[p->end_pos]) && !is_bra(p->line[p->end_pos][0])
	// 		&& !is_pipe(p->line[p->end_pos]) && !is_redirection(p->line[p->end_pos]))
	// 	{
	// 		p->start_pos = p->end_pos;
	// 		p->include_right = true;
	// 		p->right = talloc(EXPANDABLE, p);
	// 	}
	// 	parser(p->right);
	// 	return ;
	// }
	return ;
}

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
	p->left = parent->left;
	p->right = parent->right;
	// node自体と，コマンドラインの分のmallocをする。
	// typeの代入と，コマンドのポインタの代入をする？（ポインタの複製。）
	// スタートポスとエンドポスの初期化をする。
	// 最初と最後は最初は一緒。
	return p;
}
// //talloc 失敗した時のエラー処理を後で書く

// void	executer(t_node *p, t_list *list)
// {
// 	if (p->type == COMMAND_LINE)
// 	{
// 		executer(p->left, list);
// 	}
// 	if (p->type == DELIMITER)
// 	{
// 		executer(p->left, list);
// 		executer(p->right, list);
// 	}
// 	if (p->type == subshell)
// 	{
// 		t_list	*shell;
// 		t_list	*command_line;
// 		exe(p->left, shell);

// 		command_line = ft_lstnew(make_command(SHELL, (char *[]){"/bin/ls", NULL}, NULL, shell));
// 	}
// }
// //stringかなんかで，
// //p->left が NULL だったら，lstnew して，登りながら，lstadd していく。


int	main(void)
{
	t_node	root;
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
	root.left = NULL;
	root.right = NULL;
	for (int i = 0; i < ARRAY_SIZE + 1; i++)
		printf("%s ", line[i]);
	printf("\n");
	parser(&root);
	return (0);
}

/*
command_line ::=
	| "(" command_line ")" delimiter command_line
	| "(" command_line ")" "|" command_line
	| "(" command_line ")"
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

command ::=
	| arguments

arguments ::=
	| redirection
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
	| "<" aim arguments
	| ">" aim arguments
	| ">>" aim arguments
	| "<<" aim arguments
*/

/*
command_line ::=
	| "(" command_line ")" delimiter command_line
	| "(" command_line ")" "|" command_line
	| "(" command_line ")"
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
	| "<" string
	| ">" string
	| ">>" string
	| "<<" string
*/