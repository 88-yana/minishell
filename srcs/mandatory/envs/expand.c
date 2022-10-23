/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:46:11 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/23 18:45:10 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/envs.h"

char	*check_env_value(t_vars *vars, char *value)
{
	t_list	*list;
	t_envs	*envs;
	char	*str;

	list = find_envs(vars->envs, value);
	if (!list)
		return (NULL);
	envs = (t_envs *)list->content;
	str = ft_strdup(envs->value);
	if (!str)
		return (NULL);
	return (str);
}

char	*replace_envs_value(t_vars *vars, char *str, size_t *i)
{
	size_t	j;
	char	*value;
	char	*content;

	if (str[*i] == '$')
		*i++;
	if (ft_isdigit(str[*i]))
	{
		*i++;
		return (NULL);
	}
	j = 0;
	while (str[*i + j])
	{
		if (!(ft_isalnum(str[*i + j]) || str[*i + j] == '_'))
			break ;
		j++;
	}
	value = substr_size_t(str, *i, j);
	if (!value)
		return (NULL);
	*i += j;
	printf("%s, %d\n", __FILE__, __LINE__);
	content = check_env_value(vars, value);
	if (!content)
		printf("%s", content);
	return (content);
}

void	check_envs(t_vars *vars, char *str)
{
	size_t	i;
	t_list	*list;
	char	quote;
	char	*content;

	quote = '\0';
	i = 0;
	while (str[i])
	{
		if (quote == SINGLEQ || quote == DOUBLEQ)
			quote = '\0';
		else if (str[i] == SINGLEQ)
			quote = SINGLEQ;
		else if (str[i] == DOUBLEQ)
			quote = DOUBLEQ;
		else if (str[i] == '$' && quote != SINGLEQ)
		{
			content = replace_envs_value(vars, str, &i);
			continue ;
		}
		printf("%c", str[i]);
		i++;
	}
}

void	expand_envs(t_vars *vars, char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		check_envs(vars, cmd[i]);
		printf("\n");
		i++;
	}
}
