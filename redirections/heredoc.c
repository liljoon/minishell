/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:37:51 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 20:46:11 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

void	readline_heredoc(int fd[], char *eof)
{
	char	*command;

	close(fd[0]);
	rl_catch_signals = 1;
	while (1)
	{
		command = readline("> ");
		if (!command)
			break ;
		else if (ft_strncmp(eof, command, ft_strlen(eof) + 1) == 0)
		{
			free(command);
			break ;
		}
		write(fd[1], command, ft_strlen(command));
		write(fd[1], "\n", 1);
		free(command);
	}
	close(fd[1]);
	exit(0);
}

int	read_heredoc(int *herdoc_fd, char *eof)
{
	pid_t	pid;
	int		fd[2];
	int		error;

	error = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler_heredoc);
		readline_heredoc(fd, eof);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &error, 0);
		if (error)
		{
			g_shell_info.exit_status = 1;
			close(fd[0]);
			return (1);
		}
		*herdoc_fd = fd[0];
	}
	return (0);
}

int	scan_heredoc(t_token *tk)
{
	char	**operator;

	operator = tk->operator;
	while (*operator)
	{
		if (ft_strncmp(*operator, "<<", 3) == 0)
		{
			if (tk->heredoc_fd != -1)
				close(tk->heredoc_fd);
			if (read_heredoc(&(tk->heredoc_fd), *(operator + 1)))
				return (1);
		}
		else
			operator--;
		operator += 2;
	}
	return (0);
}

int	scan_heredoc_all(t_token *tks)
{
	t_token	*idx;

	idx = tks;
	while (idx)
	{
		if (scan_heredoc(idx))
			return (1);
		idx = idx->next;
	}
	return (0);
}

void	set_heredoc(t_token *tk)
{
	dup2(tk->heredoc_fd, STDIN_FILENO);
	close(tk->heredoc_fd);
}
