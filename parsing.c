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

// #include "minishell.h"
#include<stdlib.h>
// size_t	ft_strlen(const char *s)
// {
// 	size_t	idx;

// 	idx = 0;
// 	while (s[idx] != '\0')
// 		idx++;
// 	return (idx);
// }
// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*p;
// 	size_t	idx;

// 	if (!s)
// 		return (NULL);
// 	idx = 0;
// 	if (start >= ft_strlen(s))
// 		len = 0;
// 	else if (ft_strlen(s) - start < len)
// 		len = ft_strlen(s) - start;
// 	p = malloc(len + 1);
// 	if (p == NULL)
// 		return (NULL);
// 	while (s[start + idx] != '\0' && idx < len)
// 	{
// 		p[idx] = s[start + idx];
// 		idx++;
// 	}
// 	p[idx] = '\0';
// 	return (p);
// }
int	count_spaces(char *str)
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
			// if (str[i] != '"')
			// 	Error;
		}
		else if (str[i] == ' ' && str[i + 1] && str[i + 1] != ' ')
			space++;
		i++;
	}
	return (space);
}

char	*ft_substr_with_double_quotes(const char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	idx;

	if (!s)
		return (NULL);
		// Error;
	idx = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	p = malloc((len + 1) - 2);
	if (p == NULL)
		return (NULL);
	while (s[start + idx] != '\0' && idx < len)
	{
		if (s[start + idx] != '"')
			p[idx] = s[start + idx];
		idx++;
	}
	p[idx] = '\0';
	return (p);
}

void	divide_op(char *str, char **argv, int argv_idx)
{
	int	i;
	int	start_idx;

	i = 0;
	start_idx = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			argv[argv_idx++] = ft_substr(str, start_idx, i - start_idx);
			start_idx = i;
			while (str[i] && str[i + 1] == '<')
				i++;
			// if (i - start_idx > 2)
			// 	Error;
			// argv[argv_idx++]
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] && str[i + 1] == '>')
				i++;
		}
		i++;
	}
}

void	divide_argv(char *command, char **argv)
{
	int		i;
	int		argv_idx;
	int		start_idx;
	char	*substr;

	i = 0;
	argv_idx = 0;
	start_idx = 0;
	while (1)
	{
		if (command[i] == '"')
		{
			i++;
			while (command[i] != '"')
				i++;
		}
		else if (command[i] == ' ' || !command[i])
		{
			substr = ft_substr_with_double_quotes(command, start_idx, i - start_idx);
			argv[argv_idx] = substr;
			argv_idx++;
			if (command[i] == ' ')
			{
				while (command[i] == ' ')
					i++;
				start_idx = i;
			}
			// divide_op(substr, argv, argv_idx);
			// operator도 분리
			else if (!command[i])
				break ;
		}
		i++;
	}
	argv[argv_idx] = NULL;
	free(command);
}

void	parse_argv() {}

#include<stdio.h>
// void	tokenize(t_token *tk, char *command_line, int start)
void	tokenize(char *command_line, int start)
{
	int		i;
	char	*command;
	char	**argv;
	char	**operator;

	i = 0;
	while (command_line[i] != '|')
		i++;
	command = ft_substr(command_line, start, i);
	printf("command:%s/ space:%d\n", command, count_spaces(command));
	argv = malloc(sizeof(char *) * (count_spaces(command) + 2));
	// if (!argv)
	// 	Error;
	divide_argv(command, argv);
	i = -1;
	while(argv[++i])
		printf("%s\n", argv[i]);
	// tk->argv = argv;
	// tk->operator = operator;
	// tk->cmd = tk->argv[0];
}

int	main()
{
	char *input = "echo        hi     >a        | cat hello";
	tokenize(input, 0);
}