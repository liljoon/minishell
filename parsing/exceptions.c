/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:33:15 by yham              #+#    #+#             */
/*   Updated: 2023/03/21 20:24:31 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_syntax_error(void)
{
	printf_err(NULL, NULL, "syntax error");
	g_shell_info.exit_status = 258;
	return (1);
}

int	check_quote(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (is_quote(command[i]))
		{
			i += step_to_last_quote(command, i, command[i]);
			if (!command[i])
				return (handle_syntax_error());
		}
		i++;
	}
	return (0);
}

int	check_redir(char *command)
{
	int	i;
	int	start;

	i = 0;
	while (command[i])
	{
		if (is_quote(command[i]))
			i += step_to_last_quote(command, i, command[i]);
		else if (is_redir(command[i]))
		{
			start = i;
			i += step_to_last_redir(command, i, command[i]);
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
