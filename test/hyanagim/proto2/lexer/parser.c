/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:00:40 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/25 17:21:01 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	parser(t_node *p)
{
	if (p->type == コマンドラインのとき）
	{
		if (かっこがあったら，
		{
			// p->left
			// p->type = コマンドライン
			if (かっこの終わりがなければ，
				error
			かっこの終わりまで，エンドポスを進める。
			if (デリミターだったら)
			{
				p->left
					デリミター
			}
			if (パイプだったら)
				p->left
					パイプドライン
			
		}
		かっこやデリミターが見つかるまで，エンドポスを進める。
		if (かっこだったら)
		{
			p->left
				パイプドライン
		}
		if (デリミターだったら，)
		{
			p->left
					デリミター

			p->right
			p->type = コマンドライン
		}
		if (NULLだったら，全体がパイプドラインだから，)
		{
			p->left
			p->type = パイプドライン
		}

	}
}

void	talloc
{
	// node自体と，コマンドラインの分のmallocをする。
	// typeの代入と，コマンドのポインタの代入をする？（ポインタの複製。）
	// スタートポスとエンドポスの初期化をする。
	// 最初と最後は最初は一緒。

}
//talloc 失敗した時のエラー処理を後で書く


void	executer(t_node *p)
{
	if (p->type == subshell)
	{
		
	}
}


















/*
command_line ::=
	| piped_commands delimiter command_line
	| "(" command_line ")" delimiter command_line
	| "(" command_line ")" "|" command_line
	| "(" command_line ")"
	| piped_commands

パイプの後にかっこがある場合がある。
piped_commands | (command_line) 的な
↑これもパイプライン？　no


delimiter ::=
	"&&"
	"||"

piped_commands ::=
	| command "|" piped_commands
	
	| command

command ::=
	| arguments

arguments ::=
	| redirection
	| redirection arguments
	| string
	| string arguments

string ::=
	| expandable <no_space> string
	| expandable
	| not_expandable <no_space> string
	| not_expandable
	| expandable_quoted <no_space> string
	| expandable_quoted

redirection ::=
	| "<" string
	| ">" string
	| ">>" string
	| "<<" string
*/