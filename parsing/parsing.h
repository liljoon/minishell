/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:52:42 by yham              #+#    #+#             */
/*   Updated: 2023/03/10 17:45:02 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

int	    count_space(char *str);
int	    count_arg_in_str(char *str);
int	    count_total_args(char *str);
int	    count_op(char **argv);

int	    divide_op(char *str, char **argv, int argv_idx);
char	**divide_argv(char *command);

char	**extract_new_argv(char *command, char **old_argv);
char	**extract_op(char **old_argv);

# endif