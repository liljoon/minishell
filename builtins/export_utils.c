/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:19:31 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 17:07:46 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**split_env(char *str)
{
	char	**ret;
	int		idx;

	ret = malloc(sizeof(char *) * 3);
	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '=')
			break ;
		idx++;
	}
	ret[0] = ft_substr(str, 0, idx);
	if (str[idx] == '\0')
		ret[1] = NULL;
	else if (str[idx] == '=' && str[idx + 1] == '\0')
		ret[1] = ft_strdup("");
	else
		ret[1] = ft_strdup(str + idx + 1);
	ret[2] = NULL;
	return (ret);
}
