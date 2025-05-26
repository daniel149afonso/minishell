/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:28:18 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/26 03:08:49 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	replace_string(char *str, char **res, int *i)
{
	char	c[2];
	int		in_single;
	int		in_double;

	if (str[*i] == '\'' && !in_double)
	{
		in_single = !in_single;
		i++;
	}
	else if (str[*i] == '"' && !in_single)
	{
		in_double = !in_double;
		i++;
	}
	else
	{
		c[0] = str[*i];
		c[1] = 0;
		*res = ft_join_and_free(res, c);
		i++;
	}
}

char	*remove_quotes(const char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		replace_string(str, &res, &i);
	}
	return (res);
}
