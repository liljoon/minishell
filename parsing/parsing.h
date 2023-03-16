/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:52:42 by yham              #+#    #+#             */
/*   Updated: 2023/03/16 21:23:49 by yham             ###   ########.fr       */
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

t_token	*tokenize(char *command);
int		check_exceptions(char *command);

int		step_to_last_quote(char *str, int idx, char quote);
int		step_to_last_redir(char *str, int idx, char redir);
int		step_to_last_space(char *str, int idx);

int		count_arg_in_str(char *str);
int		count_total_args(char *str);
int		count_op(char **argv);
int		count_and_free_sub(char *str, int start, int len);

void	divide_op(char *str, t_argv *argv);
char	**divide_argv(char *command);
void	init_argv(t_argv *argv, char *command);
void	div_and_free_sub(t_argv *argv, char *str, int start, int len);

char	**extract_new_argv(char *command, char **old_argv);
char	**extract_op(char **old_argv);

#endif