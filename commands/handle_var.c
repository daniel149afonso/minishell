/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:15:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/05/02 15:31:17 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

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

// char	*expand_variables(char *str, t_env *env)
// {
// 	int		i = 0;
// 	char	*res = ft_calloc(1, 1); // string vide pour commencer
// 	if (!res)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			char *var_name = extract_var_name(str, &i);
// 			char *value = get_env_value(env, var_name);
// 			if (value)
// 				res = ft_join_and_free(res, value);  // ajoute la valeur trouvée
// 			free(var_name);
// 			free(value);
// 		}
// 		else
// 		{
// 			char c[2] = {str[i], 0}; // créer une string d'un seul char
// 			res = ft_join_and_free(res, c);
// 			i++;
// 		}
// 	}
// 	return (res);
// }

// void	search_var(char **strs, t_env *env)
// {
// 	int		i;
// 	char	*var;

// 	i = 0;
// 	var = NULL;
// 	while (strs[i])
// 	{
// 		if (ft_strchr(strs[i], '\''))
// 		{
// 			return ;
// 		}
// 		if (ft_strchr(strs[i], '$'))
// 		{
// 			var = expand_variables(strs[i], env);
// 			free(strs[i]);
// 			strs[i] = var;
// 		}
// 		i++;
// 	}
// }
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

void	search_var(char **strs, t_env *env)
{
	int		i;
	char	*var;

	i = 0;
	var = NULL;
	while (strs[i])
	{
		if (ft_strchr(strs[i], '$'))
		{
			var = expand_variables(strs[i], env);
			free(strs[i]);
			strs[i] = var;
		}
		i++;
	}
}
