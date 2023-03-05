/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:01:17 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/05 19:57:56 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*command;
	t_token	*tks;
	int		std_fd[2];

	set_signal();
	init_environ(envp);
	tks = malloc(sizeof(t_token));
	while (1)
	{
		command = readline("minishell$ ");
		if (!command)
		{
			printf("\033[1A");
			printf("\033[11C");
			printf("exit\n");
			exit(0);
		}
		if (command && *command)
			add_history(command);
		if (!*command)
			continue ;
		copy_std_fd(std_fd);
		tokenize(tks, command);
		if (!exec_builtins(tks))
			exec_command(tks);
		free(command);
		restore_std_fd(std_fd);
	}
}
