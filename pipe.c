/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:05:12 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/27 16:32:52 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fork한 상태에서 실행되어야 함.
void	set_pipe(char *commands, int n)
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
			close(fd[1]);
			dup2(fd[0], 0);
		}
		else
		{
			close(fd[0]);
			dup2(fd[1], 1);
			// commands parsing 하고 실행
		}
	}
	// 마지막 commands parsing 하고 실행
}
