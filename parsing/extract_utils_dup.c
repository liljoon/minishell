/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils_dup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:57:14 by yham              #+#    #+#             */
/*   Updated: 2023/03/17 15:00:10 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	init_dup_tool(t_dup_tool *dup, char *s)
{
	if (check_env(s))
		dup->src = include_env(s);
	else
		dup->src = ft_strdup(s);
	dup->res = malloc(ft_strlen(dup->src) + 1);
	dup->idx = 0;
}

int	step_and_dup(t_dup_tool *dup, char *str, int idx, char quote)
{
	int	step;

	step = 1;
	while (str[idx + step] && str[idx + step] != quote)
	{
		dup->res[dup->idx++] = str[idx + step];
		step++;
	}
	return (step);
}

char	*my_strdup(char *s)
{
	int			i;
	t_dup_tool	dup;

	init_dup_tool(&dup, s);
	i = 0;
	while (dup.src[i])
	{
		if (dup.src[i] == '\'' || dup.src[i] == '\"')
			i += step_and_dup(&dup, dup.src, i, dup.src[i]);
		else
			dup.res[dup.idx++] = dup.src[i];
		i++;
	}
	dup.res[dup.idx] = '\0';
	free(dup.src);
	return (dup.res);
}