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

#include "minishell.h"

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
// char	*ft_strdup(const char *s1)
// {
// 	int		s1_len;
// 	int		idx;
// 	char	*p;

// 	s1_len = ft_strlen(s1);
// 	p = malloc(s1_len + 1);
// 	if (p == 0)
// 		return (p);
// 	idx = 0;
// 	while (s1[idx] != '\0')
// 	{
// 		p[idx] = s1[idx];
// 		idx++;
// 	}
// 	p[idx] = '\0';
// 	return (p);
// }

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
			// if (str[i] != '"')
			// 	Error;
		}
		else if (str[i] == ' ' && str[i + 1] && str[i + 1] != ' ')
			space++;
		i++;
	}
	return (space);
}

int	count_op(char **argv)
{
	int	i;
	int	op;

	i = 0;
	op = 0;
	while (argv[i])
	{
		if (argv[i][0] == '<' ||argv[i][0] == '>')
			op++;
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

// void	divide_argv(char *command, char **argv)
// {
// 	int		i;
// 	int		argv_idx;
// 	int		start_idx;
// 	char	*substr;

// 	i = 0;
// 	argv_idx = 0;
// 	start_idx = 0;
// 	while (1)
// 	{
// 		if (command[i] == '"')
// 		{
// 			i++;
// 			while (command[i] != '"')
// 				i++;
// 		}
// 		else if (command[i] == ' ' || !command[i])
// 		{
// 			substr = ft_substr_with_double_quotes(command, start_idx, i - start_idx);
// 			argv[argv_idx] = substr;
// 			argv_idx++;
// 			if (command[i] == ' ')
// 			{
// 				while (command[i] == ' ')
// 					i++;
// 				start_idx = i;
// 			}
// 			// divide_op(substr, argv, argv_idx);
// 			// operator도 분리
// 			else if (!command[i])
// 				break ;
// 		}
// 		i++;
// 	}
// 	argv[argv_idx] = NULL;
// 	free(command);
// }

char	**divide_argv(char *command)
{
	int		i;
	int		start_idx;
	int		argv_idx;
	char	**argv;

	argv = malloc(sizeof(char *) * (count_space(command) + 1 + 1));
	// if (!argv)
	// 	Error;
	i = 0;
	start_idx = 0;
	argv_idx = 0;
	while (1)
	{
		if (!command[i] || command[i] == ' ')
		{
			argv[argv_idx++] = ft_substr(command, start_idx, i - start_idx);
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
	// if (!new_argv)
	// 	Error;
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
	// if (!operator)
	// 	Error;
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

// void	tokenize(char *command_line, int start)
void	tokenize(t_token *tk, char *command_line, int start)
{
	int		i;
	char	*command;
	char	**old_argv;
	char	**new_argv;
	char	**operator;

	// i = 0;
	// while (command_line[i] != '|')
	// 	i++;
	// command = ft_substr(command_line, start, i);
	old_argv = divide_argv(command);
	new_argv = extract_new_argv(command, old_argv);
	operator = extract_op(old_argv);
	free(old_argv);
	tk->argv = new_argv;
	tk->operator = operator;
	tk->cmd = tk->argv[0];
}