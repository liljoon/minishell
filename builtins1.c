/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:06:13 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/19 21:42:14 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(char *command, char **envp)
{
	return ;
}

void	exec_echo(char *command, char **envp)
{
	char	**argv;
	int		idx;

	idx = 1;
	argv = ft_split(command, ' ');
	if (ft_strncmp("-n", argv[1], 3) == 0)
		idx = 2;
	while (argv[idx])
	{
		if (argv[idx][0] == '$')
			printf("%s", getenv(&(argv[idx][1])));
		else
			printf("%s", argv[idx]);
		if (argv[idx + 1] != NULL)
			printf(" ");
		idx++;
	}
	if (ft_strncmp("-n", argv[1], 3) != 0)
		printf("\n");
	clear_all(argv);
	return ;
}

void	exec_cd(char *command, char **envp)
{
	char	**argv;

	argv = ft_split(command, ' ');
	if (chdir(argv[1]) == -1)
		printf("minishell: %s: %s: %s\n", argv[0], argv[1], strerror(errno));
	clear_all(argv);
	return ;
}

void	exec_pwd(char *command, char **envp)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

int	exec_builtins(char *command, char **envp)
{
	if (ft_strncmp(command, "echo", 4) == 0)
		exec_echo(command, envp);
	else if (ft_strncmp(command, "cd", 2) == 0)
		exec_cd(command, envp);
	else if (ft_strncmp(command, "pwd", 3) == 0)
		exec_pwd(command, envp);
	else if (ft_strncmp(command, "export", 6) == 0)
		exec_export(command, envp);
	else if (ft_strncmp(command, "unset", 5) == 0)
		exec_unset(command, envp);
	else if (ft_strncmp(command, "env", 3) == 0)
		exec_env(command, envp);
	else if (ft_strncmp(command, "exit", 4) == 0)
	{
		printf("exit\n");
		exit(0);
	}
	else
		return (0);
	return (1);
}
