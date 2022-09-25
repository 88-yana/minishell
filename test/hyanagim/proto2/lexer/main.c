/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:49:14 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/25 13:22:02 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdbool.h>
#include "get_next_line.h"

// typedef struct s_check
// {
// 	int		ok_line;
// 	int		ok_hairetu;
// 	char	**temp;
// }	t_check;

// t_check	lexer(char *line);

// typedef struct s_split
// {
// 	char	*line;
// 	size_t	pos;
// 	size_t	size;
// 	size_t	dquote;
// 	size_t	squote;
// 	char	**array;
// }	t_array;

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		i;
	char	**temp;
	t_array	data;

	t_array *ptr;
	// fd = open("corner.txt", O_RDONLY);
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_line(fd);
		if (line == NULL)
			break ;
		printf("%d : %s\n", i + 1, line);
		data.line = line;
		ptr = lexer(&data);
		if (ptr == NULL)
			exit(1);
		printf("size is %zu\n", ptr->size);
		int j = 0;
		while(ptr->array[j] != NULL)
		{
			printf("data is 『%s』\n", ptr->array[j]);
			j++;
		}

		parser(&data);
		
		printf("\n");
		// i = 0;
		// while (temp[i] != NULL)
		// {
		// 	printf("%s\n", temp[i]);
		// 	i++;
		// }
		// free(line);
		// free(temp);
		i++;
	}
	close(fd);

	// system("leaks -q a.out");
	exit (0);
}
