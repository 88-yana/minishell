#include "../../../includes/execution.h"
#include "../../../includes/lexer_two_symbols.h"

// bool	match_asterisk(char *file, char *str)
// {
// 	char	**words;
// 	size_t	i;
// 	size_t	j;
// 	size_t	file_len;
// 	size_t	word_len;

// 	i = 0;
// 	words = ft_split(str, '*');
// 	while (words[i])
// 	{
// 		file_len = ft_strlen(file);
// 		word_len = ft_strlen(words[i]);
// 		file = ft_strnstr(file, words[i], file_len);
// 		if (!file)
// 		{
// 			safe_free_double_char(words);
// 			return (false);
// 		}
// 		j = 0;
// 		while (j < word_len)
// 		{
// 			file++;
// 			j++;
// 		}
// 		i++;
// 	}
// 	safe_free_double_char(words);
// 	return (true);
// }

// char	**expand_asterisk(char *str)
// {
// 	DIR				*dir;
// 	size_t			i;
// 	struct dirent	*dirent;
// 	char			*cwd;

// 	cwd = getcwd(NULL, 0);
// 	dir = opendir(cwd);
// 	free(cwd);
// 	while (true)
// 	{
// 		dirent = readdir(dir);
// 		if (!dirent)
// 			break ;
// 		if (match_asterisk(dirent->d_name, str))
// 			printf("%s\n", dirent->d_name);
// 	}
// 	closedir(dir);
// 	return (NULL);
// }

// static bool	has_asterisk(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '*')
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

// void	check_asterisk(char **cmd)
// {
// 	size_t	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (has_asterisk(cmd[i]))
// 		{
// 			expand_asterisk(cmd[i]);
// 			// add to list
// 		}
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	check_asterisk((char *[]){"*", NULL});
// }

#define CWD 0
#define ASTERISK 1

bool check_front(char *file, char *str)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != '*')
	{
		if (str[i] != file[i])
			return (false);
		i++;
	}
	return (true);
}

bool check_back(char *file, char *str)
{
	size_t i;
	size_t j;
	size_t len_str;
	size_t len_file;

	len_str = ft_strlen(str);
	len_file = ft_strlen(file);
	if (len_str == 0 || len_file == 0 || str[len_str - 1] == '*')
		return (true);
	i = len_str - 1;
	j = len_file - 1;
	while (i >= 0 && j >= 0 && str[i] != '*')
	{
		if (str[i] != file[j])
			return (false);
		i--;
		j--;
	}
	return (true);
}

bool match_asterisk(char *file, char *str)
{
	char **words;
	size_t i;
	size_t j;
	size_t file_len;
	size_t word_len;

	i = 0;
	if (!check_front(file, str) || !check_back(file, str))
		return (false);
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

char **clip_latter(char **cmd, size_t start)
{
	char **latter;
	size_t size;
	size_t i;

	size = arraylen(cmd) - start;
	latter = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (cmd[start + i] != NULL)
	{
		latter[i] = cmd[start + i];
		i++;
	}
	latter[i] = NULL;
	return (latter);
}

char **realloc_array(char **cmd, char *str, size_t size)
{
	char **new;
	size_t i;

	new = malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (i < size)
	{
		new[i] = cmd[i];
		i++;
	}
	new[size] = str;
	new[size + 1] = NULL;
	// free(cmd);
	return (new);
}

char **expand_asterisk(char ***cmd, size_t pos)
{
	DIR *dir;
	size_t i;
	struct dirent *dirent;
	char **latter;
	char *s[2];

	s[ASTERISK] = (*cmd)[pos];
	latter = clip_latter(*cmd, pos + 1);
	s[CWD] = getcwd(NULL, 0);
	dir = opendir(s[CWD]);
	free(s[CWD]);
	while (true)
	{
		dirent = readdir(dir);
		if (!dirent)
			break;
		if (match_asterisk(dirent->d_name, s[ASTERISK]))
			*cmd = realloc_array(*cmd, dirent->d_name, pos++);
	}
	*cmd = arrayjoin(*cmd, latter);
	closedir(dir);
	return (NULL);
}

static bool has_asterisk(char *str)
{
	size_t i;

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
	size_t i;

	i = 0;
	while (cmd[i])
	{
		if (has_asterisk(cmd[i]))
		{
			expand_asterisk(cmd, i);
		}
		i++;
	}
}

//int main(void)
//{
//	check_asterisk((char *[]){"hello", "*.", "hello", NULL});
//}
