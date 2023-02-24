/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:11:58 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/24 20:08:00 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_output(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
}

void	redirection_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	dup2(fd, 0);
}

void	redirection_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
}

void	redirection_heredoc(char *arg)
{
	int		temp_fd;
	int		fd;
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
		write(temp_fd,	"\n", 1);
		free(command);
	}
	fd = open("./.heredoc_temp", O_RDONLY);
	dup2(fd, 0);
}

char	*check_redirection_output(char *command)
{
	char	**str_arr;
	int		fd;

	str_arr = ft_split(command, '>');
	if (str_arr[1] == NULL)
		return (str_arr[0]);
	str_arr[1] = ft_strtrim(str_arr[1], " ");
	fd = open(str_arr[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	return (str_arr[0]);
}

char	*check_redirections(char *command)
{

}
