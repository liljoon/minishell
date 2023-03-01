/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:17:56 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/01 16:54:30 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(char *argv[])
{
	while (*argv)
	{
		find_and_del_env(*argv);
		argv++;
	}
}

void	exec_env(void)
{
	t_node	*idx;

	idx = g_shell_info.envl;
	while (idx != NULL)
	{
		if (ft_strchr(idx->data, '='))
			printf("%s\n", idx->data);
		idx = idx->next;
	}
}
