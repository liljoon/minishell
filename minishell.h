/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:01:29 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/06 23:57:48 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include "./linked_list/linked_list.h"

typedef struct s_shell_info
{
	int exit_status;
	t_node *envl;
} t_shell_info;

typedef struct s_token
{
	char *cmd;
	char **argv;
	char **operator;
	struct s_token *next;
} t_token;

t_shell_info g_shell_info;

void set_signal(void);
void exec_command(t_token *tk);
int exec_builtins(t_token *tk);
void exec_unset(char *argv[]);
void exec_env(void);
void trans_env(char *argv[]);
void check_redirections(t_token *tk);
void init_environ(char *envp[]);
char *my_getenv(char *_data);
char **get_envp(void);
void set_pipe(char *commands[], int n);
void find_and_del_env(char *_data);
void modify_env(char *name, char *data);
void tokenize(t_token *tk, char *command);

void copy_std_fd(int fd[]);
void restore_std_fd(int fd[]);

void free_token(t_token *tk);
void free_chars(char **chars);
void free_all_tks(t_token **head);

t_token *split_pipe_and_tokenize(char *command);

#endif
