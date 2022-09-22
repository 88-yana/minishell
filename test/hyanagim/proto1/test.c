
# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<stdbool.h>

typedef enum e_symbol {
	COMMAND_LINE,
	SEQUENCIAL_COMMANDS,
	PIPED_COMMANDS,
	COMMAND,
	ARGUMENTS,
	STRING,
	REDIRECTION
}	t_symbol;

typedef struct s_tree {
	t_symbol		type;
	char			*line;
	void			*elem;
	struct s_tree	*parent;
	struct s_tree	*child_left;
	struct s_tree	*child_right;
}	t_tree;


typedef struct s_vars {
	t_tree	*tree;
	int		lexer_size;
	int		lexer_pos;
}	t_vars;

char    *strjoin(char *s1, char *s2)
{
    char *str = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));

    size_t i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    size_t j = 0;
    while (s2[j])
    {
        str[i + j] = s2[j];
        j++;
    }
    str[i + j] = '\0';
    return (str);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	vars.tree = malloc(sizeof(t_tree));
	vars.tree->type = COMMAND_LINE;
	vars.tree->line = NULL;
	printf("%s\n", *envp);
	while (true)
	{
		vars.tree->line = readline("minishell > ");
		if (vars.tree->line == NULL || strlen(vars.tree->line) == 0)
		{
			free(vars.tree->line);
			break ;
		}
		add_history(vars.tree->line);
		if (strncmp(vars.tree->line, "/bin/", 5) == 0)
		{
			char *cmds[] = {vars.tree->line, NULL};
			execve(cmds[0], cmds, envp);
		}
		else
		{
			char *cmd = strjoin("/bin/", vars.tree->line);
			char *cmds[] = {cmd, NULL};
			execve(cmds[0], cmds, envp);
		}
		// handle_parser(vars.tree);
		free(vars.tree->line);
	}
	return (0);
}