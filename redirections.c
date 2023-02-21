/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:11:58 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/21 12:43:21 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_redirection_output(char *command)
{
	char	**str_arr;
	int		fd;

	str_arr = ft_split(command, '>');
	if (str_arr[1] == NULL)
		return (str_arr[0]);
	str_arr[1] = ft_strtrim(str_arr[1], " ");
	fd = open(str_arr[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	return (str_arr[0]);
}


char	*check_redirections(char *command)
{

}
