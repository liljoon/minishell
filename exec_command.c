/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:36:25 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/21 16:37:49 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path(char *argv[], char *envp[])
{
	char	*path;
	char	**paths;
	char	*old_argv0;

	if (argv[0][0] == '/')
	{
		execve(argv[0], argv, envp);
		printf("minishell: %s: %s\n", argv[0], strerror(errno));
	}
	else
	{
		old_argv0 = argv[0];
		path = getenv("PATH");
		paths = ft_split(path, ':');
		while (*paths)
		{
			argv[0] = old_argv0;
			argv[0] = ft_strjoin("/", argv[0]);
			argv[0] = ft_strjoin(*paths, argv[0]);
			execve(argv[0], argv, envp);
			paths++;
		}
		printf("minishell: %s: command not found\n", old_argv0);
	}
}

void	trans_env(char *argv[])
{
	while (*argv)
	{
		if ((*argv)[0] == '$')
		{
			if ((*argv)[1] == '?')
				*argv = ft_itoa(g_exit_status);
			else
				*argv = getenv(&(*argv)[1]);
		}
		argv++;
	}
}

char	**split_one_pipe(char *command)
{
	char	**commands;

	commands = malloc(sizeof(char *) * 2);
	if (ft_strchr(command, '|') == NULL)
	{
		commands[0] = command;
		commands[1] = NULL;
		return (commands);
	}
	commands[0] = ft_substr(command, 0, ft_strchr(command, '|') - command - 1);
	commands[1] = ft_strchr(command, '|') + 1;
	return (commands);
}

void	exec_command(char *command, char *envp[])
{
	pid_t	pid;
	char	**argv;
	int		fd[2];
	char	**commands;

	//commands = split_one_pipe(command);
	//pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		//close(fd[1]);
		//dup2(fd[0], 0);
		commands[0] = check_redirection_output(commands[0]);
		argv = ft_split(commands[0], ' ');
		if (*argv == NULL)
			exit(0);
		trans_env(argv);
		check_path(argv, envp);
		exit(127);
	}
	else
	{
		//close(fd[0]);
		//dup2(fd[1], 1);
		waitpid(pid, &g_exit_status, 0);
		g_exit_status /= 256;
	}
	return ;
}

void	split_pipe(char *command, char *envp[])
{
	char	**commands;

	commands = ft_split(command, '|');
	while (*commands)
	{
		exec_command(*commands, envp);
		commands++;
	}
}
