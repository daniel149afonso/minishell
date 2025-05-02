/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:51:01 by apiscopo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/30 17:43:24 by daafonso         ###   ########.fr       */
=======
/*   Updated: 2025/04/30 16:21:12 by apiscopo         ###   ########.fr       */
>>>>>>> krool
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*extract_key(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*extract_value(char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

static void	update_or_add_var(t_env **env, char *arg)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	int		found;

	key = extract_key(arg);
	value = extract_value(arg);
	tmp = *env;
	found = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = value;
			found = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!found)
		add_env_node(env, arg);
	free(key);
	if (!found)
		free(value);
}

void	check_if_var(t_env **env)
{
	t_list	*arg;
	t_list	*tmp;
	char	*value;

	arg = (*env)->lst->next;
	tmp = (*env)->lst->next;
	while(tmp)
	{
		value = extract_check_key(tmp->content);
		if (value[0] == '=')
		{
			printf("export: `%s': not a valid identifier\n", value);
			tmp = tmp->next;
			value = extract_check_key(tmp->content);
			if (value)
				printf("export: `%s': not a valid identifier\n", value);
			return ;
		}
		tmp = tmp->next;
	}
	while (arg)
	{
		update_or_add_var(env, (char *)arg->content);
		arg = arg->next;
	}
}

void	ft_exp(t_env *env)
{
	t_env	*tmp;
	t_list	*lst;

	tmp = env;
	lst = env->lst;
	f_bubblesort(lst);
	if (!lst || !lst->next)
	{
		while (tmp)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
			tmp = tmp->next;
		}
	}
	else
		check_if_var(&env);
}
