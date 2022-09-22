#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sysexits.h>
#include <signal.h>
#include <stdlib.h>  
#include <unistd.h>
#include <string.h>

#define READ  (0)
#define WRITE (1)

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
		char *command;
		
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

		// 子プロセスはここで該当プログラムを起動しリターンしない
		// if (execlp("sh", "sh", "-c", command, NULL) < 0) {
		// 	perror("popen2");
		// 	close(pipe_parent2child[READ]);
		// 	close(pipe_child2parent[WRITE]);
		// 	return 1;
		// }
	}

	// 親プロセス側の処理
	close(pipe_parent2child[READ]);
	close(pipe_child2parent[WRITE]);

	*fd_r = pipe_child2parent[READ];
	*fd_w = pipe_parent2child[WRITE];

	return pid;
}

int	main(int argc, char *argv[])
{
	int fd_r = fileno(stdin);
	int fd_w = fileno(stdout);
	popen2(&fd_r, &fd_w);
	write(fd_w, argv[1], strlen(argv[1]));
	char buf[255];
	int size;
	size = read(fd_w, buf, 255);
	printf("'%s'\n", buf);
	printf("write is '%s'", buf);
	// char buf[255];
	// int size;
	// size = read(fd_r, buf, 255);
	// printf("buf is %s", buf);

	// popen2("echo hello", &fd_r, &fd_w);
	// size = read(fd_r, buf, 255);
	// printf("buf is %s", buf);
	return 0;
}


// int	main()
// {
// 	char str[512], *ptr;
// 	FILE *fp;
// 	if ((fp = popen("ls -1", "r")) == NULL)
// 		return (1);
// 	while (true)
// 	{
// 		fgets(str, 512, fp);
// 		if (feof(fp))
// 			break ;
// 		ptr = strchr(str, '\n');
// 		if (ptr != NULL)
// 			*ptr = '\0';
// 		printf("%s\n", str);
// 	}
// 	pclose(fp);
// 	return (0);
// }