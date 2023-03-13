/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:37:51 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/11 20:44:13 by isunwoo          ###   ########.fr       */
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
		else if (ft_strncmp(arg, command, ft_strlen(arg)) == 0)
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

void	check_heredoc_first(t_token *tk)
{
	char	**operator;
	int		flag;
	int		fd;

	flag = 0;
	operator = tk->operator;
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
	if (flag)
	{
		fd = open("./.heredoc_temp", O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
}
