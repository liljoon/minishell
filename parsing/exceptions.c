/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:33:15 by yham              #+#    #+#             */
/*   Updated: 2023/03/15 16:53:46 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_syntax_error(void)
{
	printf_err(NULL, NULL, "syntax error");
	return (1);
}

int	check_quote(char *command)
{
	int		i;
	char	quote;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
		{
			quote = command[i];
			while (command[i + 1] && command[i + 1] != quote)
				i++;
			if (!command[i + 1])
				return (handle_syntax_error());
			i++;
		}
		i++;
	}
	return (0);
}

int	check_redir(char *command)
{
	int		i;
	int		start;
	char	quote;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
		{
			quote = command[i];
			while (command[++i] && command[++i] != quote)
				;
		}
		else if (command[i] == '<' || command[i] == '>')
		{
			start = i;
			while ((command[i] == '<' && command[i + 1] == '<')
				|| (command[i] == '>' && command[i + 1] == '>'))
				i++;
			if (i - start + 1 > 2)
				return (handle_syntax_error());
		}
		i++;
	}
	return (0);
}

int	check_exceptions(char *command)
{
	if (check_quote(command))
		return (1);
	else if (check_redir(command))
		return (1);
	else
		return (0);
}
