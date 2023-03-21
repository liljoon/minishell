/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:37:51 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/21 12:29:34 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

void	sig_handler(int signo)
{
	if (signo == SIGINT)
		exit(1);
}

int	read_heredoc(int *herdoc_fd, char *eof)
{
	pid_t	pid;
	int		fd[2];
	char	*command;
	int		error;

	error = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_handler);
		close(fd[0]);
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
	else
	{
		close(fd[1]);
		waitpid(pid, &error, 0);
		if (error)
		{
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
