/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:06:13 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/03 15:06:54 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(char *argv[])
{
	t_node	*idx;

	argv++;
	if (*argv == NULL)
	{
		idx = g_shell_info.envl;
		while (idx != NULL)
		{
			printf("declare -x %s\n", idx->data);
			idx = idx->next;
		}
		return ;
	}
	while (*argv)
	{
		push_back(&g_shell_info.envl, *argv);
		argv++;
	}
}

void	exec_echo(char *argv[])
{
	int		idx;

	idx = 1;
	if (argv[1] && ft_strncmp("-n", argv[1], 3) == 0)
		idx = 2;
	while (argv[idx])
	{
		printf("%s", argv[idx]);
		if (argv[idx + 1] != NULL)
			printf(" ");
		idx++;
	}
	if (!(argv[1] && ft_strncmp("-n", argv[1], 3) == 0))
		printf("\n");
	return ;
}

void	exec_cd(char *argv[])
{
	char	*temp_dir;

	temp_dir = getcwd(NULL, 0);
	if (argv[1] == NULL)
		chdir(my_getenv("HOME"));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		chdir(my_getenv("OLDPWD"));
	else if (argv[1][0] == '~')
	{
		if (chdir(ft_strjoin(my_getenv("HOME"), &(argv[1][1]))) == -1)
			printf("minishell: %s: %s: %s\n", argv[0], argv[1], strerror(errno));
	}
	else if (chdir(argv[1]) == -1)
		printf("minishell: %s: %s: %s\n", argv[0], argv[1], strerror(errno));
	modify_env("OLDPWD", temp_dir);
	free(temp_dir);
	return ;
}

void	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

int	exec_builtins(t_token *tk)
{
	if (ft_strncmp(tk->cmd, "echo", 5) == 0)
		exec_echo(tk->argv);
	else if (ft_strncmp(tk->cmd, "cd", 3) == 0)
		exec_cd(tk->argv);
	else if (ft_strncmp(tk->cmd, "pwd", 4) == 0)
		exec_pwd();
	else if (ft_strncmp(tk->cmd, "export", 7) == 0)
		exec_export(tk->argv);
	else if (ft_strncmp(tk->cmd, "unset", 6) == 0)
		exec_unset(tk->argv);
	else if (ft_strncmp(tk->cmd, "env", 4) == 0)
		exec_env();
	else if (ft_strncmp(tk->cmd, "exit", 5) == 0)
	{
		printf("exit\n");
		exit(0);
	}
	else
		return (0);
	return (1);
}
