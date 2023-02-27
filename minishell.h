/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:01:29 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/26 21:30:29 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./linked_list/linked_list.h"

typedef struct s_shell_info{
	int		exit_status;
	t_node	*envl;
}	t_shell_info;

t_shell_info	g_shell_info;

void	set_signal(void);
void	exec_command(char *command, char *envp[]);
int		exec_builtins(char *command, char **envp);
void	exec_unset(char *argv[]);
void	exec_env(void);
void	trans_env(char *argv[]);
void	split_pipe(char *command, char *envp[]);
char	*check_redirection_output(char *command);
void	redirection_heredoc(char *arg);
void	init_environ(char *envp[]);
void	print_all_env(void);
char	*my_getenv(char *_data);


#endif
