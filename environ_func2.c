/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:04:32 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/17 18:11:56 by isunwoo          ###   ########.fr       */
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

char	**get_envp(void)
{
	char	**ret;
	int		idx;
	t_node	*temp;

	idx = 0;
	temp = g_shell_info.envl;
	while (temp)
	{
		idx++;
		temp = temp->next;
	}
	ret = malloc(sizeof(char *) * (idx + 1));
	idx = 0;
	temp = g_shell_info.envl;
	while (temp)
	{
		ret[idx] = malloc(sizeof(char *) * (ft_strlen(temp->data) + 1));
		ft_strlcpy(ret[idx], temp->data, ft_strlen(temp->data) + 1);
		idx++;
		temp = temp->next;
	}
	ret[idx] = NULL;
	return (ret);
}
