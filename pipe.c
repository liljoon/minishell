/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:05:12 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/09 22:00:55 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_token(t_token *tk)
{
	if (!check_redirections(tk) && !exec_builtins(tk))
		check_path_and_exec(tk->argv);
	exit(127);
}

void	set_pipe_and_exec(t_token *tks, int n)
{
	int		fd[2];
	pid_t	pid;

	while (tks->next)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			exec_token(tks);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			waitpid(pid, &g_shell_info.exit_status, 0);
			g_shell_info.exit_status /= 256;
		}
		tks = tks->next;
	}
	exec_token(tks);
}
