/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:51:58 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/26 16:51:24 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environ(char *envp[])
{
	while (*envp)
	{
		push_back(&(g_shell_info.envl), *envp);
		envp++;
	}
}

void	print_all_env(void)
{
	t_node	*idx;

	idx = g_shell_info.envl;
	while (idx != NULL)
	{
		printf("%s\n", idx->data);
		idx = idx->next;
	}
}
