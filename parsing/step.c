/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:09:35 by yham              #+#    #+#             */
/*   Updated: 2023/03/21 20:27:34 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	step_to_last_quote(char *str, int idx, char quote)
{
	int	step;

	step = 1;
	while (str[idx + step] && str[idx + step] != quote)
		step++;
	return (step);
}

int	step_to_last_redir(char *str, int idx, char redir)
{
	int	step;

	step = 1;
	while (str[idx + step] == redir)
		step++;
	return (--step);
}

int	step_to_last_space(char *str, int idx)
{
	int	step;

	step = 1;
	while (is_space(str[idx + step]))
		step++;
	return (--step);
}

int	step_to_last_alpha(char *str, int idx)
{
	int	step;

	step = 0;
	while ((str[idx + step] >= 'a' && str[idx + step] <= 'z')
		|| (str[idx + step] >= 'A' && str[idx + step] <= 'Z'))
		step++;
	if (step == 0)
		return (step);
	else
		return (--step);
}
