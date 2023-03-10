/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:22:22 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/09 22:22:28 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exec_export(char *argv[])
{
	t_node	*idx;

	argv++;
	if (*argv == NULL)
	{
		idx = g_shell_info.envl;
		while (idx != NULL)
		{
			printf("declare -x %s\n", idx->data);
			idx = idx->next;
		}
		return ;
	}
	while (*argv)
	{
		push_back(&g_shell_info.envl, *argv);
		argv++;
	}
}
