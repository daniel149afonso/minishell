/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:55:58 by daafonso          #+#    #+#             */
/*   Updated: 2025/06/04 22:13:29 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*extract_var_name(char *str, int *i)
{
	int		len;
	int		j;
	char	*name;

	len = 0;
	while (str[*i + len] && is_var_char(str[*i + len]))
		len++;
	name = malloc(len + 1);
	if (!name)
		return (0);
	j = 0;
	while (j < len)
	{
		name[j] = str[*i + j];
		j++;
	}
	name[j] = '\0';
	*i += len;
	return (name);
}

char	*get_env_value(t_env *env, char *var_name)
{
	t_env	*tmp;
	char	*value;

	value = NULL;
	while (env)
	{
		tmp = env->next;
		if (ft_strcmp(env->key, var_name) == 0)
		{
			value = ft_strdup(env->value);
			if (!value)
				return (NULL);
		}
		env = tmp;
	}
	return (value);
}
