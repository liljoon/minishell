/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:37:51 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/17 16:43:03 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

void	redirection_heredoc(char *arg)
{
	int		temp_fd;
	char	*command;

	temp_fd = open("./.heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		command = readline("> ");
		if (!command)
			break ;
		else if (ft_strncmp(arg, command, ft_strlen(arg) + 1) == 0)
		{
			free(command);
			break ;
		}
		write(temp_fd, command, ft_strlen(command));
		write(temp_fd, "\n", 1);
		free(command);
	}
	close(temp_fd);
}

void	sig_handler(int signo)
{
	exit(1);
}

void	scan_heredoc_and_exit(char **operator)
{
	int	flag;

	flag = 0;
	signal(SIGINT, sig_handler);
	while (*operator)
	{
		if (ft_strncmp(*operator, "<<", 3) == 0)
		{
			redirection_heredoc(*(operator + 1));
			flag = 1;
		}
		else
			operator--;
		operator += 2;
	}
	if (!flag)
		exit(2);
	else
		exit(0);
}

int	check_heredoc_first(t_token *tk)
{
	int		fd;
	pid_t	pid;
	int		ex_st;

	pid = fork();
	if (pid == 0)
		scan_heredoc_and_exit(tk->operator);
	else
	{
		waitpid(pid, &ex_st, 0);
		if (ex_st == 0)
		{
			fd = open("./.heredoc_temp", O_RDONLY);
			dup2(fd, 0);
			close(fd);
			return (0);
		}
		else if (ex_st == 512)
			return (0);
		else
			return (1);
	}
	return (0);
}
