/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:01:40 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 14:44:26 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_numeric(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	exec_exit(char **argv)
{
	int	argv_len;

	argv_len = count_string_arr_len(argv);
	write(2, "exit\n", 5);
	if (argv_len == 0)
		return ;
	if (!is_numeric(argv[1]))
	{
		printf_err("exit", NULL, "too many arguments");
		g_shell_info.exit_status = 255;
		exit(g_shell_info.exit_status);
	}
	if (argv_len == 1)
		exit(g_shell_info.exit_status);
	else if (argv_len == 2)
		exit(ft_atoi(argv[1]));
	else
	{
		printf_err("exit", NULL, "too many arguments");
		g_shell_info.exit_status = 1;
	}
}
