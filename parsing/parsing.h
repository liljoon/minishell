/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:52:42 by yham              #+#    #+#             */
/*   Updated: 2023/03/21 20:24:06 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

typedef struct s_argv
{
	char	**data;
	int		idx;
}	t_argv;

typedef struct s_env_tool
{
	int		start;
	char	*res;
}	t_env_tool;

typedef struct s_dup_tool
{
	char	*src;
	char	*res;
	int		idx;
	int		null_flag;
}	t_dup_tool;

t_token	*tokenize(char *command);
int		check_exceptions(char *command);
void	init_token(t_token *tk, char **_argv, char **_operator);
void	init_token_null(t_token *tk);
int		is_quote(char c);
int		is_redir(char c);
int		is_space(char c);

int		step_to_last_quote(char *str, int idx, char quote);
int		step_to_last_redir(char *str, int idx, char redir);
int		step_to_last_space(char *str, int idx);
int		step_to_last_alpha(char *str, int idx);

int		count_arg_in_str(char *str);
int		count_total_args(char *str);
int		count_op(char **argv);
int		count_and_free_sub(char *str, int start, int len);

char	**divide_argv(char *command);
void	divide_and_free_sub(t_argv *argv, char *str, int start, int len);

char	**extract_new_argv(char *command, char **old_argv);
void	extract_op(t_token *tk, char **old_argv, char **new_argv);
char	*my_strdup(char *s);
char	*include_env(char *s);

#endif