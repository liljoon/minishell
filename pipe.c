/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:05:12 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 17:17:22 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_token(t_token *tk)
{
	if (!check_redirections(tk, tk->operator) \
		&& *(tk->argv) && !exec_builtins(tk))
		check_path_and_exec(tk->argv);
	exit(127);
}

void	child_process(int temp_fd, int fd[], t_token *tks)
{
	if (temp_fd != -1)
		dup2(temp_fd, 0);
	close(temp_fd);
	close(fd[0]);
	if (tks->next)
		dup2(fd[1], 1);
	close(fd[1]);
	exec_token(tks);
}

void	wait_all(pid_t pid, int n)
{
	int	stat;

	while (n--)
	{
		if (wait(&stat) == pid)
			g_shell_info.exit_status = WEXITSTATUS(stat);
	}
}

void	set_pipe_and_exec(t_token *tks, int n)
{
	int		fd[2];
	pid_t	pid;
	int		temp_fd;

	temp_fd = -1;
	while (tks)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			child_process(temp_fd, fd, tks);
		else
		{
			if (temp_fd != -1)
				close(temp_fd);
			close(fd[1]);
			temp_fd = fd[0];
		}
		tks = tks->next;
	}
	close(temp_fd);
	wait_all(pid, n);
}
