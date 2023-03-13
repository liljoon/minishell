/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:07:09 by yham              #+#    #+#             */
/*   Updated: 2023/03/11 22:08:50 by yham             ###   ########.fr       */
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
	int		start_idx;
	int		flag;
	char	quote;
	char	*ret;

	i = 0;
	quote = 0;
	start_idx = 0;
	ret = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		else if (s[i] == '$')
		{
			if (i > 0)
				ret = my_strjoin(ret, ft_substr(s, start_idx, i - start_idx));
			start_idx = ++i;
			if (!s[i])
			{
				ret = my_strjoin(ret, ft_substr(s, start_idx - 1, 1));
				break ;
			}
			while ((s[i] >= 'a' && s[i] <= 'z')
					|| (s[i] >= 'A' && s[i] <= 'Z'))
				i++;
			if (i - start_idx == 0)
			{
				if (s[i] == '?')
				{
					ret = my_strjoin(ret, ft_itoa(g_shell_info.exit_status));
					start_idx = ++i;;
				}
				continue ;
			}
			// char *temp = my_getenv(ft_substr(s, start_idx, i - start_idx));
			ret = my_strjoin(ret, ft_strdup(my_getenv(ft_substr(s, start_idx, i - start_idx))));
			start_idx = i;
		}
		i++;
	}
	if (i - start_idx > 0)
		ret = my_strjoin(ret, ft_substr(s, start_idx, i - start_idx));
	// free(s);
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
	int		slen;
	char	*p;

	if (check_env(s))
		s = include_env(s);
	slen = ft_strlen(s);
	p = malloc(slen + 1);
	if (p == 0)
		return (p);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			continue ;
		}
		p[j] = s[i];
		i++;
		j++;
	}
	p[j] = '\0';
	return (p);
}

char	**extract_new_argv(char *command, char **old_argv)
{
	int		i;
	int		new_idx;
	char	quote;
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * (count_total_args(command) + 1 - count_op(old_argv) * 2 + 1));
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
			new_argv[new_idx++] = my_strdup(old_argv[i]);
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
