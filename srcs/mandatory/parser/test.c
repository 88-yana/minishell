#include	"../../../includes/parser.h"

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
	command_line->pipe_num = -1;
	command_line->read_fd = -1;
	command_line->write_fd = -1;
	command_line->next_read_fd = -1;
	command_line->can_exec = true;
	if (type == SUBSHELL)
		command_line->shell = shell;
	else
		command_line->shell = NULL;
	return (command_line);
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
			printf("---------- inside shell ----------\n");
			printf("type: [ %s ]\n", "shell");
			display_command(command->shell);
			printf("---------- inside shell ----------\n");
		}
		else if (command->type == GT)
		{
			printf("type: [ %s ]", "gt");
			printf(" aim: [ %s ]\n", command->file);
		}
		else if (command->type == LT)
		{
			printf("type: [ %s ]", "lt");
			printf(" aim: [ %s ]\n", command->file);
		}
		else if (command->type == GTGT)
		{
			printf("type: [ %s ]", "gtgt");
			printf(" aim: [ %s ]\n", command->file);
		}
		else if (command->type == LTLT)
		{
			printf("type: [ %s ]", "ltlt");
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

// void size_index(t_list **list, t_node *p, t_type type)
// {
// 	int i = 0;
// 	while (list[i] != NULL)
// 		i++;
// 	if (type == COMMAND)
// 		printf("in command %d\n", i);
// 	if (type == ARGUMENTS)
// 		printf("in arguments %d\n", i);
// 	if (type == REDIRECTION)
// 		printf("in  %d\n", i);
// 	printf("index is %zu\n\n", p->index);
// }

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
"(" command_line ")" > text.txt ←これも存在する。

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
	| (subshell)
	| (subshell) arguments

command ::=
	| expandable <no_space> command
	| expandable
	| not_expandable <no_space> command
	| not_expandable
	| expandable_quoted <no_space> command
	| expandable_quoted

redirection ::=
	| < aim
	| >  aim
	| >>  aim
	| <<  aim
	| <aim //後でやる。
	| >aim //後でやる。
	| >>aim //
	| <<aim //
*/