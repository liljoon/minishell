/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:01:29 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 22:10:35 by isunwoo          ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h>
# include <termios.h>
# include "./libft/libft.h"
# include "./linked_list/linked_list.h"

typedef struct s_shell_info
{
	int		exit_status;
	t_node	*envl;
}	t_shell_info;

typedef struct s_token
{
	char			*cmd;
	char			**argv;
	char			**operator;
	int				heredoc_fd;
	struct s_token	*next;
}	t_token;

t_shell_info	g_shell_info;

void	set_signal(void);
void	set_signal_before_exec(void);
void	fork_and_exec(t_token *tk);
void	exec_control(t_token *tks);
int		exec_builtins(t_token *tk);

void	trans_env(char *argv[]);
int		check_redirections(t_token *tk, char **operator);
int		scan_heredoc_all(t_token *tks);
void	init_environ(char *envp[]);
t_node	*find_env_node(char *str);
char	*my_getenv(char *_data);
char	**get_envp(void);
void	set_pipe_and_exec(t_token *tks, int n);
void	check_path_and_exec(char *argv[]);
void	find_and_del_env(char *_data);
void	modify_env(char *name, char *data);

void	copy_std_fd(int fd[]);
void	restore_std_fd(int fd[]);

void	free_token(t_token *tk);
void	free_chars(char **chars);
void	free_all_tks(t_token **head);

t_token	*split_pipe_and_tokenize(char *command);

void	printf_err(char *arg0, char *arg1, char *err);

#endif
