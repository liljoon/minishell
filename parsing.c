/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:51:25 by yham              #+#    #+#             */
/*   Updated: 2023/02/21 19:08:55 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx] != '\0')
		idx++;
	return (idx);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	idx;

	if (!dst && !src)
		return (dst);
	idx = 0;
	while (idx < n)
	{
		*((unsigned char *)dst + idx) = *((unsigned char *)src + idx);
		idx++;
	}
	return (dst);
}

static int	count_words(char const *s, char c)
{
	int	flag;
	int	idx;
	int	res;

	res = 0;
	idx = 0;
	flag = 0;
	while (s[idx])
	{
		if (s[idx] != c && !flag)
		{
			res++;
			flag = 1;
		}
		else if (s[idx] == c && flag)
			flag = 0;
		idx++;
	}
	return (res);
}

static int	str_len(const char *str, char c)
{
	int	idx;

	idx = 0;
	while (str[idx] != c && str[idx] != '\0')
		idx++;
	return (idx);
}

static char	*copy(char const *s, int length)
{
	char	*res;

	res = malloc(sizeof(char) * (length + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, s, length);
	res[length] = '\0';
	return (res);
}

char	**clear_all(char **res)
{
	int	idx;

	idx = 0;
	while (res[idx])
	{
		free(res[idx]);
		idx++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		words_cnt;
	char	**res;
	int		words_idx;
	int		str_idx;

	if (!s)
		return (NULL);
	words_idx = 0;
	str_idx = 0;
	words_cnt = count_words(s, c);
	res = malloc(sizeof(char *) * (words_cnt + 1));
	if (!res)
		return (res);
	while (words_idx < words_cnt)
	{
		while (s[str_idx] == c)
			str_idx++;
		res[words_idx] = copy(s + str_idx, str_len(s + str_idx, c));
		if (!res[words_idx])
			return (clear_all(res));
		str_idx += str_len(s + str_idx, c);
		words_idx++;
	}
	res[words_idx] = 0;
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	idx;

	if (!s)
		return (NULL);
	idx = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	p = malloc(len + 1);
	if (p == NULL)
		return (NULL);
	while (s[start + idx] != '\0' && idx < len)
	{
		p[idx] = s[start + idx];
		idx++;
	}
	p[idx] = '\0';
	return (p);
}

void	parse_command(char *command)
{
	char	*parsed;
	int		i;
	int		start;
	char	*env;

	parsed = "";
	i = -1;
	start = 0;
	while (command[++i])
	{
		if (command[i] == '$')
		{
			printf("%s", ft_substr(command, start, i - start));
			i++;
			start = i;
			while (!(command[i] == '$' || command[i] == '\0'))
				i++;
			env = getenv(ft_substr(command, start, i - start));
			if (!env)
				return ;
			printf("%s", env);
			start = i;
		}
	}
	printf("%s ", ft_substr(command, start, i - start));
	return ;
}
/*
int	main(void)
{
	char	**splited;
	int		i;

	splited = ft_split("a $HOMEb c$HOME bbb", ' ');
	i = -1;
	while (splited[++i])
		parse_command(splited[i]);
}
*/