/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:15:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/05/02 01:56:27 by daniel149af      ###   ########.fr       */
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

// void	search_puts_var(t_env *env, char *arg)
// {
// 	t_env	*tmp;
// 	char	*key;
// 	char	*value;
// 	int		found;

// 	printf("Before name: %s\n", arg);
// 	key = extract_key(arg);
// 	value = extract_value(arg);
// 	printf("key: %s, value: %s\n", key, value);
// 	if (!key || !value)
// 	{
// 		printf("key or value does not exist\n");
// 		return ;
// 	}
// 	tmp = env;
// 	found = 0;
// 	printf("DEBUG | looking for: %s\n", key);
// 	while (tmp)
// 	{
// 		printf("DEBUG | checking key: %s\n", tmp->key);
// 		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
// 		{
// 			free(tmp->value);
// 			tmp->value = value;
// 			found = 1;
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (found)
// 		printf("%s", tmp->value);
// 	if (key)
// 		free(key);
// 	if (value)
// 		free(value);
// }


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
	char	*res = ft_calloc(1, 1); // string vide pour commencer
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			char *var_name = extract_var_name(str, &i);
			char *value = get_env_value(env, var_name);
			if (value)
				res = ft_join_and_free(res, value);  // ajoute la valeur trouvée
			free(var_name);
			free(value);
		}
		else
		{
			char c[2] = {str[i], 0}; // créer une string d'un seul char
			res = ft_join_and_free(res, c);
			i++;
		}
	}
	printf("Value: %s\n", res);
	return (res);
}

void	display_without_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'')
			printf("%c", str[i]);
		i++;
	}
	
}

void	search_var(char **strs, t_env *env)
{
	int		i;
	char	*var;
	
	i = 0;
	var = NULL;
	while (strs[i])
	{
		if (ft_strchr(strs[i], '\''))
		{
			return ;
		}
		if (ft_strchr(strs[i], '$'))
		{
			var = expand_variables(strs[i], env);
			free(strs[i]);
			strs[i] = var;
		}
		i++;
	}
}
