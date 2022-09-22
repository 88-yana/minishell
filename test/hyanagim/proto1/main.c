/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:34:15 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/16 19:58:28 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ  (0)
#define WRITE (1)

//*fd_r 読み込み用ファイルディスクリプタ
//*fd_w 書き込み用ファイルディスクリプタ

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

int popen2(int *fd_r, int *fd_w) {

	// 子から親への通信用パイプ
	int pipe_child2parent[2];

	// 親から子への通信用パイプ
	int pipe_parent2child[2];

	// プロセスID
	int pid;

	// パイプを生成
	pipe(pipe_child2parent);

	// パイプを生成
	pipe(pipe_parent2child);


	// fork
	pid = fork();
	// 子プロセスか？
	if (pid == 0) {
		// 子プロセスの場合は、親→子への書き込みはありえないのでcloseする
		close(pipe_parent2child[WRITE]);

		// 子プロセスの場合は、子→親の読み込みはありえないのでcloseする
		close(pipe_child2parent[READ]);

		// 親→子への出力を標準入力として割り当て
		dup2(pipe_parent2child[READ], 0);

		// 子→親への入力を標準出力に割り当て
		dup2(pipe_child2parent[WRITE], 1);

		// 割り当てたファイルディスクリプタは閉じる
		close(pipe_parent2child[READ]);
		close(pipe_child2parent[WRITE]);


		char *str[] = {"/bin/echo", "42", NULL};
		char *stt[] = {"/bin/echo", "hello", NULL};
		// 子プロセスはここで該当プログラムを起動しリターンしない
		if (execv("/bin/echo", str) < 0) {
			perror("popen2");
			close(pipe_parent2child[READ]);
			close(pipe_child2parent[WRITE]);
			return 1;
		}
		if (execv("/bin/echo", stt) < 0) {
			perror("popen2");
			close(pipe_parent2child[READ]);
			close(pipe_child2parent[WRITE]);
			return 1;
		}
	}

	// 親プロセス側の処理
	close(pipe_parent2child[READ]);
	close(pipe_child2parent[WRITE]);

	*fd_r = pipe_child2parent[READ];
	*fd_w = pipe_parent2child[WRITE];

	return pid;
}

int main(int argc, char *argv[]/* , char *env */) {
	int fd_r = fileno(stdin);
	int fd_w = fileno(stdout);

	if (argc < 2) {
		printf("Usage: %s <message>\n", argv[0]);
		return 1;
	}

	popen2(&fd_r, &fd_w);

	write(fd_w, argv[1], strlen(argv[1]));

	char buf[255];
	int size;
	size = read(fd_r, buf, 255);
	if (size == -1) {
		perror("error");
		return 1;
	}
	printf("test2:");
	fwrite(buf, 1, size, stdout);
	printf("buf is %s", buf);
	printf("\n");

	return 0;
}

