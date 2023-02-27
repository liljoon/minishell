/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:51:58 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/27 18:14:39 by isunwoo          ###   ########.fr       */
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
		if (ft_strchr(idx->data, '='))
			printf("%s\n", idx->data);
		idx = idx->next;
	}
}

char	*my_getenv(char *_data)
{
	t_node	*idx;

	idx = g_shell_info.envl;
	while (idx != NULL)
	{
		if (ft_strncmp(idx->data, _data, ft_strlen(_data)) == 0 && \
			(*(idx->data + ft_strlen(_data)) == '=' || *(idx->data + ft_strlen(_data)) == 0))
			break ;
		idx = idx->next;
	}
	if (idx == NULL || *(idx->data + ft_strlen(_data)) != '=')
		return ("");
	return (idx->data + ft_strlen(_data) + 1);
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
