/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:07:09 by yham              #+#    #+#             */
/*   Updated: 2023/03/16 21:18:08 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*my_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	idx_p;
	char	*p;

	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (NULL);
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

char	*include_env(char *s)
{
	int		i;
	int		start;
	int		flag;
	char	quote;
	char	*sub;
	char	*ret;

	i = 0;
	quote = 0;
	start = 0;
	ret = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
			i++;
		}
		else if (s[i] == '$')
		{
			if (i > 0)
				ret = my_strjoin(ret, ft_substr(s, start, i - start));
			start = ++i;
			if (!s[i])
			{
				ret = my_strjoin(ret, ft_substr(s, start - 1, 1));
				break ;
			}
			while ((s[i] >= 'a' && s[i] <= 'z')
				|| (s[i] >= 'A' && s[i] <= 'Z'))
				i++;
			if (i - start == 0)
			{
				if (s[i] == '?')
				{
					ret = my_strjoin(ret, ft_itoa(g_shell_info.exit_status));
					start = ++i;
				}
				continue ;
			}
			sub = ft_substr(s, start, i - start);
			ret = my_strjoin(ret, ft_strdup(my_getenv(sub)));
			free(sub);
			start = i;
			continue ;
		}
		i++;
	}
	if (i - start > 0)
		ret = my_strjoin(ret, ft_substr(s, start, i - start));
	return (ret);
}

int	check_env(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*my_strdup(char *s)
{
	int		i;
	int		j;
	int		env_flag;
	char	quote;
	char	*dup;

	env_flag = 0;
	if (check_env(s))
	{
		s = include_env(s);
		env_flag = 1;
	}
	dup = malloc(ft_strlen(s) + 1);
	if (dup == 0)
		return (dup);
	i = 0;
	j = 0;
	quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && (!quote || s[i] == quote))
		{
			if (!quote)
				quote = s[i];
			else if (s[i] == quote)
				quote = 0;
		}
		else
		{
			dup[j] = s[i];
			j++;
		}
		i++;
	}
	dup[j] = '\0';
	if (env_flag)
		free(s);
	return (dup);
}

char	**extract_new_argv(char *command, char **old_argv)
{
	int		i;
	int		new_idx;
	char	quote;
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * (count_total_args(command) - (count_op(old_argv) * 2) + 1));
	i = 0;
	new_idx = 0;
	while (old_argv[i])
	{
		if (old_argv[i][0] == '<' || old_argv[i][0] == '>')
		{
			if (!old_argv[i + 1])
				break ;
			i++;
		}
		else
		{
			new_argv[new_idx] = my_strdup(old_argv[i]);
			new_idx++;
		}
		i++;
	}
	new_argv[new_idx] = NULL;
	return (new_argv);
}

char	**extract_op(char **old_argv)
{
	int		i;
	int		op_idx;
	char	**operator;

	operator = malloc(sizeof(char *) * (count_op(old_argv) * 2 + 1));
	i = 0;
	op_idx = 0;
	while (old_argv[i])
	{
		if (old_argv[i][0] == '<' || old_argv[i][0] == '>')
		{
			operator[op_idx] = ft_strdup(old_argv[i]);
			op_idx++;
			i++;
			if (!old_argv[i])
				break ;
			operator[op_idx] = my_strdup(old_argv[i]);
			op_idx++;
		}
		i++;
	}
	operator[op_idx] = NULL;
	return (operator);
}
