/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:52:22 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/15 19:29:41 by apiscopo         ###   ########.fr       */
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
	while (env)
	{
		if ((ft_strncmp(env->key, "?", 1) == 0))
		{
			env->value = ft_itoa(error_code);
			break ;
		}
		env = env->next;
	}
}
