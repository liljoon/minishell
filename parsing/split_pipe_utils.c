/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:20:20 by yham              #+#    #+#             */
/*   Updated: 2023/03/24 21:44:37 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	substitute_pipe(char *command)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
		{
			if (quote == 0)
				quote = command[i];
			else if (quote == command[i])
				quote = 0;
		}
		else if (command[i] == '|' && !quote)
			command[i] = -1;
		i++;
	}
}

void	trim_splited_command(char **splited_command)
{
	char	*temp;

	while (*splited_command)
	{
		temp = *splited_command;
		*splited_command = ft_strtrim(*splited_command, " ");
		free(temp);
		splited_command++;
	}
}

int	count_pipe(char *command)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (command[i])
	{
		if (command[i] == (char)-1)
			pipe++;
		i++;
	}
	return (pipe);
}

int	check_pipe(char *command, char **splited_command)
{
	int	i;

	i = 0;
	while (splited_command[i] && splited_command[i][0])
		i++;
	if (i != count_pipe(command) + 1)
		return (1);
	else
		return (0);
}
