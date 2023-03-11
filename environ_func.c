/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:51:58 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/10 18:04:46 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_str(char *env_str, char *str)
{
	if (ft_strncmp(env_str, str, ft_strlen(str)) == 0 && \
		(*(env_str + ft_strlen(str)) == '=' || \
		*(env_str + ft_strlen(str)) == 0))
		return (1);
	else
		return (0);
}

void	init_environ(char *envp[])
{
	while (*envp)
	{
		push_back(&(g_shell_info.envl), *envp);
		envp++;
	}
}

void	find_and_del_env(char *_data)
{
	t_node	*temp;
	t_node	*before;

	temp = g_shell_info.envl;
	if (g_shell_info.envl == NULL)
		return ;
	while (temp != NULL)
	{
		if (is_env_str(temp->data, _data))
			break ;
		before = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	if (temp == g_shell_info.envl)
		g_shell_info.envl = temp->next;
	else
		before->next = temp->next;
	del_node(temp);
}

char	*my_getenv(char *_data)
{
	t_node	*idx;

	idx = g_shell_info.envl;
	while (idx != NULL)
	{
		if (is_env_str(idx->data, _data))
			break ;
		idx = idx->next;
	}
	if (idx == NULL || *(idx->data + ft_strlen(_data)) != '=')
		return ("");
	return (idx->data + ft_strlen(_data) + 1);
}

void	modify_env(char *name, char *data)
{
	t_node	*idx;
	char	*old;
	char	*new_str;

	idx = g_shell_info.envl;
	while (idx)
	{
		if (is_env_str(idx->data, name))
			break ;
		idx = idx->next;
	}
	if (idx == NULL)
		return ;
	old = idx->data;
	if (data)
		new_str = malloc(ft_strlen(name) + ft_strlen(data) + 2);
	else
		new_str = malloc(ft_strlen(name) + 2);
	ft_strlcpy(new_str, name, ft_strlen(name) + 1);
	if (data)
	{
		ft_strlcat(new_str, "=", ft_strlen(name) + 2);
		ft_strlcat(new_str, data, ft_strlen(name) + ft_strlen(data) + 2);
	}
	idx->data = new_str;
	free(old);
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
