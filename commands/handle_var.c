/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:15:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/05/24 19:16:14 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

char	*expand_variables(char *str, t_env *env)
{
	int		i = 0;
	int		in_single = 0;
	int		in_double = 0;
	char	*res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		// Gérer les quotes
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
			continue;
		}
		else if (str[i] == '"' && !in_single)
		{
			in_double = !in_double;
			i++;
			continue;
		}

		// Gérer $ seulement si on est HORS de quotes simples
		if (str[i] == '$' && !in_single)
		{
			i++;
			char *var = extract_var_name(str, &i);
			char *val = get_env_value(env, var);
			if (val)
				res = ft_join_and_free(res, val);
			free(var);
			continue;
		}

		// Ajouter le caractère normalement
		char c[2] = {str[i], 0};
		res = ft_join_and_free(res, c);
		i++;
	}
	return (res);
}

char	**search_var(char **strs, t_env *env)
{
	int		i;
	char	*var;

	i = 0;
	while (strs[i])
	{
		var = expand_variables(strs[i], env);
		free(strs[i]);
		strs[i] = var;
		i++;
	}
	return (strs);
}
