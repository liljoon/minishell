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

#include "minishell.h"

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

int	count_arg_in_str(char *str)
{
	int	i;
	int	arg;

	i = 0;
	arg = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (i > 0)
				arg++;
			if ((str[i] == '<' && str[i + 1] && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] && str[i + 1] == '>'))
				i++;
			arg++;
		}
		i++;
	}
	if (str[i - 1] && str[i - 1] != '<' && str[i - 1] != '>')
		arg++;
	return (arg);
}

int	count_total_args(char *str)
{
	int		i;
	int		args;
	int		start_idx;
	char	quote;
	char	*sub;

	i = 0;
	args = 0;
	start_idx = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			if (i > 0)
			{
				sub = ft_substr(str, start_idx, i - start_idx);
				args += count_arg_in_str(sub);
				free(sub);
			}
			while (str[i] == ' ')
				i++;
			start_idx = i;
			continue ;
		}
		i++;
	}
	sub = ft_substr(str, start_idx, i - start_idx);
	args += count_arg_in_str(sub);
	free(sub);
	return (args);
}

int	count_op(char **argv)
{
	int	i;
	int	j;
	int	op;

	i = 0;
	op = 0;
	while (argv[i])
	{
		if (argv[i][0] == '<' || argv[i][0] == '>')
			op++;
		i++;
	}
	return (op);
}

int	divide_op(char *str, char **argv, int argv_idx)
{
	int		i;
	int		start_idx;
	int		cnt;

	i = 0;
	start_idx = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (i > 0)
			{
				argv[argv_idx + cnt] = ft_substr(str, start_idx, i - start_idx);
				cnt++;
			}
			if ((str[i] == '<' && str[i + 1] && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] && str[i + 1] == '>'))
			{
				argv[argv_idx + cnt] = ft_substr(str, i, 2);
				i++;
			}
			else
				argv[argv_idx + cnt] = ft_substr(str, i, 1);
			i++;
			cnt++;
			start_idx = i;
			continue ;
		}
		i++;
	}
	if (str[i - 1] && str[i - 1] != '<' && str[i- 1] != '>')
	{
		argv[argv_idx + cnt] = ft_substr(str, start_idx, i - start_idx);
		cnt++;
	}
	return (cnt);
}

int	check_op(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

char	**divide_argv(char *command)
{
	int		i;
	int		start_idx;
	int		argv_idx;
	char	quote;
	char	*sub;
	char	**argv;

	argv = malloc(sizeof(char *) * (count_total_args(command) + 1));
	i = 0;
	start_idx = 0;
	argv_idx = 0;
	while (command[i])
	{
		if (command[i] == ' ')
		{
			if (i > 0)
			{
				sub = ft_substr(command, start_idx, i - start_idx);
				if (check_op(sub))
					argv_idx += divide_op(sub, argv, argv_idx);
				else
					argv[argv_idx++] = ft_strdup(sub);
				free(sub);
			}
			while (command[i] == ' ')
				i++;
			start_idx = i;
			continue ;
		}
		i++;
	}
	sub = ft_substr(command, start_idx, i - start_idx);
	if (check_op(sub))
		argv_idx += divide_op(sub, argv, argv_idx);
	else
		argv[argv_idx++] = ft_strdup(sub);
	free(sub);
	argv[argv_idx] = NULL;
	return (argv);
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
			i++;
		else if (old_argv[i][0] == '\'' || old_argv[i][0] == '\"')
			new_argv[new_idx++] = ft_substr(old_argv[i], 1, ft_strlen(old_argv[i]) - 2);
		else
			new_argv[new_idx++] = ft_strdup(old_argv[i]);
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
			operator[op_idx++] = ft_strdup(old_argv[i]);
			op_idx++;
		}
		i++;
	}
	operator[op_idx] = NULL;
	return (operator);
}

// void	tokenize(char *command)
t_token	*tokenize(char *command)
{
	int		i;
	char	**old_argv;
	char	**new_argv;
	char	**operator;
	t_token	*tk;

	tk = malloc(sizeof(t_token));
	// printf("args:%d\n", count_total_args(command));
	old_argv = divide_argv(command);
	new_argv = extract_new_argv(command, old_argv);
	operator = extract_op(old_argv);
	tk->argv = new_argv;
	tk->operator = operator;
	tk->cmd = tk->argv[0];
	tk->next = NULL;
	// i = -1;
	// while (old_argv[++i])
	// 	printf("old:%s\n", old_argv[i]);
	// i = -1;
	// while (new_argv[++i])
	// 	printf("new:%s\n", new_argv[i]);
	// i = -1;
	// while (operator[++i])
	// 	printf("op:%s\n", operator[i]);
	free_chars(old_argv);
	return (tk);
}
