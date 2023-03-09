/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:05:12 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/09 21:46:09 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe_and_exec(t_token *tks, int n)
{
	int		fd[2];
	int		idx;
	pid_t	pid;

	idx = 0;
	while (idx < n - 1)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			check_redirections(tks);
			if (!exec_builtins(tks))
				check_path_and_exec(tks->argv);
			exit(127);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			waitpid(pid, &g_shell_info.exit_status, 0);
			g_shell_info.exit_status /= 256;
		}
		tks = tks->next;
		idx++;
	}
	check_redirections(tks);
	if (!exec_builtins(tks))
		check_path_and_exec(tks->argv);
	exit(127);
}
