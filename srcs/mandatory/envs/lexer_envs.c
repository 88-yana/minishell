/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:55:12 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/23 21:47:04 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/envs.h"

// int g_status = 0;

# define DQ 0
# define SQ 1

// char	**split(char **array, char *line)
// {
// 	size_t	i;
// 	size_t	str_len;

// 	i = 0;
// 	str_len = 0;
// 	while (1)
// 	{
// 		if (data->line[i] == '$')
// 			plus_pos(data, &i, &str_len);
// 		if (data->line[i] == '\0')
// 		{
// 			push_element_div(data, i, str_len, type);
// 			str_len = 0;
// 		}
// 		else
// 			str_len++;
// 		if (data->line[i] == '\0')
// 			break ;
// 		i++;
// 	}
// }

// static void	plus_pos(t_array *data, size_t *i, size_t *str_len)
// {
// 	go_advance(i, str_len);
// 	if (ft_isalnum(data->line[*i]) || data->line[*i] == '_')
// 		handle_env(data, i, str_len);
// 	else
// 		return ;
// }

char	*check_env_value(t_vars *vars, char *env)
{
	t_list	*list;
	t_envs	*envs;
	char	*value;

	list = find_envs(vars->envs, env);
	if (!list)
		return ("");
	envs = (t_envs *)list->content;
	value = ft_strdup(envs->value);
	return (value);
}

char	*handle_env(t_vars *vars, char *line, size_t *pos)
{
	size_t	start;
	char	*env;

	if (ft_isdigit(line[*pos]))
	{
		(*pos)++;
		start = *pos;
		while (ft_isalnum(line[*pos]) || line[*pos] == '_')
			(*pos)++;
		return (substr_size_t(line, start, (*pos) - start));
	}
	start = (*pos);
	while (ft_isalnum(line[*pos]) || line[*pos] == '_')
		(*pos)++;
	env = substr_size_t(line, start, (*pos) - start);
	if (env == NULL)
		return (NULL);
	return (check_env_value(vars, env));
}

static char	*divide(t_vars *vars, char *line, size_t *pos, bool during[2])
{
	size_t	start;
	// printf("during is %d\n", during[SQ]);
	// printf("c is %c\n", line[(*pos)]);
	if (line[(*pos)] == '$' && (during[SQ] == false || during[DQ] == true))
	{
		(*pos)++;
		if (ft_isalnum(line[*pos]) || line[*pos] == '_')
			return (handle_env(vars, line, pos));
		else if (line[*pos] == '?')
		{
			(*pos)++;
			return (ft_itoa(g_status % 256));
		}
		else
			(*pos)--;
	}
	start = *pos;
	while (line[*pos] == '$')
		(*pos)++;
	while (line[*pos] != '$' && line[*pos] != '\0')
	{
		// printf("109 is %d\n", (during[SQ]));
		// printf("110 is %c\n", line[*pos]);
		(*pos)++;
		if (line[*pos] == SINGLEQ)
			(during[SQ]) = !(during[SQ]);
	}
	return (substr_size_t(line, start, (*pos) - start));
}

char	*lexer_envs(t_vars *vars, char *line)
{
	char	*divided_line;
	char	*temp;
	size_t	pos;
	size_t	start;
	bool	during[2];

	pos = 0;
	divided_line = ft_strdup("");
	if (divided_line == NULL)
		return (NULL);
	during[SQ] = false;
	during[DQ] = false;
	while (line[pos] != '\0')
	{
		if (line[pos] == SINGLEQ)
			during[SQ] = !during[SQ];
		if (line[pos] == DOUBLEQ)
			during[DQ] = !during[DQ];
		// printf("133 %d\n", during[SQ]);
		start = pos;
		temp = divide(vars, line, &pos, during);
		// printf("136 %d\n", during[SQ]);
		if (temp == NULL)
		{
			free(temp);
			return (NULL);
		}
		divided_line = ft_strjoin(divided_line, temp);
	}
	return (divided_line);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	line[] = "abc$?345";
// 	char	line1[] = "abc'$345678'";
// 	char	line2[] = "echo $PATH";
// 	char	line3[] = "\'\"abc$PATH\"\'";
// 	char	line4[] = "\"abc$PATH''\"";
// 	char	line5[] = "$$$";
// 	char	line6[] = "$+-abc";
// 	char	line7[] = "$+-abc$PATH";
// 	char	line8[] = "$$PATH";
// 	char	line9[] = "$";
// 	char	line10[] = "\"\'$PATH\'\"";
// 	char	line11[] = "\'\"$PATH\"\'$PATH\"\'\'$PATH\'\'\"";
// 	char	*made;
// 	t_vars	vars;

// 	convert_envp_to_list(&vars, envp);
// 	made = lexer_envs(&vars, line);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line1);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line2);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line3);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line4);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line5);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line6);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line7);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line8);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line9);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line10);
// 	printf("%s\n", made);
// 	made = lexer_envs(&vars, line11);
// 	printf("%s\n", made);
// }
