/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:11:58 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/11 20:44:16 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

void	redirection_output(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
}

int	redirection_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf_err(file, NULL, strerror(errno));
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

void	redirection_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
}

int	check_redirections(t_token *tk)
{
	char	**operator;

	check_heredoc_first(tk);
	operator = tk->operator;
	while (*operator)
	{
		if (ft_strncmp(*operator, ">", 2) == 0)
			redirection_output(*(operator + 1));
		else if (ft_strncmp(*operator, "<", 2) == 0)
		{
			if (redirection_input(*(operator + 1)))
				return (1);
		}
		else if (ft_strncmp(*operator, ">>", 3) == 0)
			redirection_append(*(operator + 1));
		else
			operator--;
		operator += 2;
	}
	return (0);
}