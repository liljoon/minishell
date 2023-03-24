/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:21:30 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 14:49:24 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
	g_shell_info.exit_status = 0;
}
