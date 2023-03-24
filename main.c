/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:01:17 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 18:09:50 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(void)
{
	printf("\033[1A");
	printf("\033[11C");
	printf("exit\n");
	exit(g_shell_info.exit_status);
}

int	command_handle(char *command)
{
	if (!command)
		exit_minishell();
	if (command && *command)
		add_history(command);
	if (!*command)
	{
		free(command);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*command;
	t_token	*tks;
	int		std_fd[2];

	if (!argc || !argv)
		return (-1);
	init_environ(envp);
	modify_env("OLDPWD", NULL);
	while (1)
	{
		set_signal();
		command = readline("minishell$ ");
		if (command_handle(command))
			continue ;
		signal(SIGINT, sigint_nothing);
		copy_std_fd(std_fd);
		tks = split_pipe_and_tokenize(command);
		exec_control(tks);
		free_all_tks(&tks);
		free(command);
		restore_std_fd(std_fd);
	}
}
