/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:49:14 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/23 17:02:04 by hyanagim         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		i;
	char	**temp;

	// fd = open("corner.txt", O_RDONLY);
	if (argc != 2)
		return (0);
	char *filename = ft_strjoin(argv[1], ".txt");
	fd = open(filename, O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_line(fd);
		if (line == NULL)
			break ;
		printf("%d : %s", i + 1, line);
		temp = lexer(line);
		printf("\n");
		// temp = lexer(line);
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
