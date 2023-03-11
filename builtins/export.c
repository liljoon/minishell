/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:22:22 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/11 18:27:27 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	count_string_arr_len(char **strings)
{
	int	idx;

	idx = 0;
	while (strings[idx])
		idx++;
	return (idx);
}

void	print_with_double_quotes(char *s)
{
	int	flag;

	printf("declare -x ");
	flag = 0;
	while (*s)
	{
		printf("%c",*s);
		if (*s == '=' && !flag)
		{
			flag = 1;
			printf("\"");
		}
		s++;
	}
	if (flag)
		printf("\"\n");
	else
		printf("\n");
}

void	print_envp_sorted(void)
{
	char	**envp;
	int		step;
	int		i;
	char	*temp;
	int		size;

	envp = get_envp();
	size = count_string_arr_len(envp);
	step = 0;
	while (step < size - 1)
	{
		i = 0;
		while (i < size - step - 1)
		{
			if (ft_strncmp(envp[i], envp[i + 1], ft_strlen(envp[i])) > 0)
				swap(&(envp[i]), &(envp[i + 1]));
			i++;
		}
		step++;
	}
	i = 0;
	while (envp[i])
		print_with_double_quotes(envp[i++]);
	free_chars(envp);
}

void	exec_export(char *argv[])
{
	t_node	*idx;

	argv++;
	if (*argv == NULL)
	{
		print_envp_sorted();
	}
	while (*argv)
	{
		push_back(&g_shell_info.envl, *argv);
		argv++;
	}
}
