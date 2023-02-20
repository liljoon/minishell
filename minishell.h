/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:01:29 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/19 22:21:50 by isunwoo          ###   ########.fr       */
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
# include "./libft/libft.h"

int	g_exit_status;

void	set_signal(void);
void	exec_command(char *command, char *envp[]);
int		exec_builtins(char *command, char **envp);
void	exec_unset(char *commmand, char **envp);
void	exec_env(char *commmand, char **envp);
void	trans_env(char *argv[]);

#endif
