/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:51:25 by yham              #+#    #+#             */
/*   Updated: 2023/03/05 20:32:45 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include<stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx] != '\0')
		idx++;
	return (idx);
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
char	*ft_strdup(const char *s1)
{
	int		s1_len;
	int		idx;
	char	*p;

	s1_len = ft_strlen(s1);
	p = malloc(s1_len + 1);
	if (p == 0)
		return (p);
	idx = 0;
	while (s1[idx] != '\0')
	{
		p[idx] = s1[idx];
		idx++;
	}
	p[idx] = '\0';
	return (p);
}

int	count_space(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
		}
		else if (str[i] == ' ' && str[i + 1] && str[i + 1] != ' ')
			space++;
		i++;
	}
	return (space);
}

int	count_op_in_str(char *str)
{
	int	i;
	int	op;

	i = 0;
	op = 0;
	while (1)
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (i > 0)
				op++;
			if ((str[i] == '<' && str[i + 1] && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] && str[i + 1] == '>'))
				i++;
			op++;
		}
		else if (!str[i])
		{
			op++;
			break ;
		}
		i++;
	}
	return (op);
}

int	count_total_args(char *str)
{
	int	i;
	int	args;
	int	start_idx;

	i = 0;
	args = 0;
	start_idx = 0;
	while (1)
	{
		if (str[i] == ' ' || !str[i])
		{
			if (i > 0)
				args += count_op_in_str(ft_substr(str, start_idx, i - start_idx));
			while (str[i] == ' ')
				i++;
			if (!str[i])
				break ;
		}
		i++;
	}
	return (args);
}

int	count_op(char **argv)
{
	int	i;
	int	op;

	i = 0;
	op = 0;
	while (argv[i])
	{
		if (argv[i][0] == '<')
		{
			if (argv[i][1] && argv[i][1] == '<')
				i++;
			op++;
		}
		else if (argv[i][0] == '>')
		{
			if (argv[i][1] && argv[i][1] == '>')
				i++;
			op++;
		}
		i++;
	}
	return (op);
}

// char	*ft_substr_with_double_quotes(const char *s, unsigned int start, size_t len)
// {
// 	char	*p;
// 	size_t	idx;

// 	if (!s)
// 		return (NULL);
// 		// Error;
// 	idx = 0;
// 	if (start >= ft_strlen(s))
// 		len = 0;
// 	else if (ft_strlen(s) - start < len)
// 		len = ft_strlen(s) - start;
// 	p = malloc((len + 1) - 2);
// 	if (p == NULL)
// 		return (NULL);
// 	while (s[start + idx] != '\0' && idx < len)
// 	{
// 		if (s[start + idx] != '"')
// 			p[idx] = s[start + idx];
// 		idx++;
// 	}
// 	p[idx] = '\0';
// 	return (p);
// }

char	**split_op(char *str)
{
	int		i;
	int		split_idx;
	int		start_idx;
	char	**splited_op;

	i = 0;
	split_idx = 0;
	start_idx = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (i > 0)
				splited_op[split_idx++] = ft_substr(str, start_idx, i - start_idx);
			if (str[i + 1] && str[i + 1] == '<')
			{
				splited_op[split_idx++] = ft_substr(str, i, 2);
				i++;
			}
			else
				splited_op[split_idx++] = ft_substr(str, i, 1);
			start_idx = i + 1;
		}
		else if (str[i] == '>')
		{
			if (i > 0)
				splited_op[split_idx++] = ft_substr(str, start_idx, i - start_idx);
			if (str[i + 1] && str[i + 1] == '>')
			{
				splited_op[split_idx++] = ft_substr(str, i, 2);
				i++;
			}
			else
				splited_op[split_idx++] = ft_substr(str, i, 1);
			start_idx = i + 1;
		}
		i++;
	}
	return (splited_op);
}

char	**divide_argv(char *command)
{
	int		i;
	int		start_idx;
	int		argv_idx;
	char	**argv;

	argv = malloc(sizeof(char *) * (count_total_args(command) + 1));
	i = 0;
	start_idx = 0;
	argv_idx = 0;
	while (1)
	{
		if (!command[i] || command[i] == ' ')
		{
			split_op(ft_substr(command, start_idx, i - start_idx));
			while (command[i] == ' ')
				i++;
			if (!command[i])
				break ;
			start_idx = i;
		}
		i++;
	}
	argv[argv_idx] = NULL;
	return (argv);
}

char	**extract_new_argv(char *command, char **old_argv)
{
	int		i;
	int		new_idx;
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * (count_space(command) + 1 - count_op(old_argv) * 2 + 1));
	i = 0;
	new_idx = 0;
	while (old_argv[i])
	{
		if (old_argv[i][0] == '<' || old_argv[i][0] == '>')
			i++;
		else
			new_argv[new_idx++] = ft_strdup(old_argv[i]);
		i++;
	}
	new_argv[new_idx] = NULL;
	return (new_argv);
}

char	**extract_op(char **old_argv)
{
	int	i;
	int	op_idx;
	char	**operator;

	operator = malloc(sizeof(char *) * (count_op(old_argv) * 2 + 1));
	i = 0;
	op_idx = 0;
	while (old_argv[i])
	{
		if (old_argv[i][0] == '<' || old_argv[i][0] == '>')
		{
			operator[op_idx++] = ft_strdup(old_argv[i]);
			i++;
			operator[op_idx++] = ft_strdup(old_argv[i]);
		}
		i++;
	}
	operator[op_idx] = NULL;
	return (operator);
}
#include<stdio.h>
// void	tokenize(t_token *tk, char *command)
void	tokenize(char *command)
{
	int		i;
	char	**old_argv;
	char	**new_argv;
	char	**operator;

	printf("args:%d\n", count_total_args(command));
	// old_argv = divide_argv(command);
	// new_argv = extract_new_argv(command, old_argv);
	// operator = extract_op(old_argv);
	// tk->argv = new_argv;
	// tk->operator = operator;
	// tk->cmd = tk->argv[0];
	// free_chars(old_argv);
	// i = -1;
	// while (old_argv[++i])
	// 	printf("argv:%s\n", old_argv[i]);
}

int	main()
{
	char	*input = "echo hi>a";
	printf("input:%s\n", input);
	tokenize(input);
}