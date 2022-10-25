#include	"../../../includes/execution.h"

bool	match_asterisk(char *file, char *str)
{
	char	**words;
	size_t	i;
	size_t	j;
	size_t	file_len;
	size_t	word_len;

	i = 0;
	words = ft_split(str, '*');
	while (words[i])
	{
		file_len = ft_strlen(file);
		word_len = ft_strlen(words[i]);
		file = ft_strnstr(file, words[i], file_len);
		if (!file)
		{
			safe_free_double_char(words);
			return (false);
		}
		j = 0;
		while (j < word_len)
		{
			file++;
			j++;
		}
		i++;
	}
	safe_free_double_char(words);
	return (true);
}

char	**expand_asterisk(char *str)
{
	DIR				*dir;
	size_t			i;
	struct dirent	*dirent;
	char			*cwd;

	cwd = getcwd(NULL, 0);
	dir = opendir(cwd);
	free(cwd);
	while (true)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (match_asterisk(dirent->d_name, str))
			printf("%s\n", dirent->d_name);
	}
	closedir(dir);
	return (NULL);
}

static bool	has_asterisk(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

void	check_asterisk(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (has_asterisk(cmd[i]))
		{
			expand_asterisk(cmd[i]);
			// add to list
		}
		i++;
	}
}

int	main(void)
{
	check_asterisk((char *[]){"*.c", NULL});
}
