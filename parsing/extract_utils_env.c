/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:57:30 by yham              #+#    #+#             */
/*   Updated: 2023/03/17 14:59:01 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_env_tool(t_env_tool *env)
{
	env->start = 0;
	env->res = ft_strdup("");
}

char	*my_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	idx_p;
	char	*p;

	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	idx_p = 0;
	while (s1[i])
	{
		p[idx_p] = s1[i];
		i++;
		idx_p++;
	}
	i = 0;
	while (s2[i])
	{
		p[idx_p] = s2[i];
		i++;
		idx_p++;
	}
	p[idx_p] = '\0';
	free(s1);
	free(s2);
	return (p);
}

char	*join_and_free_sub(char *joined, char *str, int start, int len)
{
	char	*sub;
	char	*ret;

	sub = ft_substr(str, start, len);
	ret = my_strjoin(joined, ft_strdup(my_getenv(sub)));
	free(sub);
	return (ret);
}

int	handle_different_envs(t_env_tool *env, char *str, int idx)
{
	if (!str[idx])
	{
		env->start = idx - 1;
		return (-1);
	}
	else if (str[idx] == '?')
	{
		env->res = my_strjoin(env->res, ft_itoa(g_shell_info.exit_status));
		env->start = idx + 1;
	}
	else
	{
		env->res \
		= join_and_free_sub(env->res, str, env->start, idx - env->start + 1);
		env->start = idx + 1;
	}
	return (0);
}

char	*include_env(char *s)
{
	int			i;
	t_env_tool	env;

	init_env_tool(&env);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			i += step_to_last_quote(s, i, s[i]);
		else if (s[i] == '$')
		{
			if (i > 0)
				env.res = \
				my_strjoin(env.res, ft_substr(s, env.start, i - env.start));
			env.start = ++i;
			i += step_to_last_alpha(s, i);
			i += handle_different_envs(&env, s, i);
		}
		i++;
	}
	if (i - env.start > 0)
		env.res = my_strjoin(env.res, ft_substr(s, env.start, i - env.start));
	return (env.res);
}
