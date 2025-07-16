/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:52:22 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/16 18:12:29 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if ((c >= '0' && c <= '9') || c == '_' || c == '?')
		return (1);
	return (0);
}

char	*ft_join_and_free(char *text, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(text, buffer);
	free(text);
	return (temp);
}

void	return_code(t_env *env, int error_code)
{
	env->error_code = error_code;
	env->var_error_code = error_code;
}

int	is_space_command(char **strs)
{
	int	i;
	int	j;

	if (!strs)
		return (1);
	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (!is_space(strs[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}