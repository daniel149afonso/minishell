/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:08:37 by apiscopo          #+#    #+#             */
/*   Updated: 2025/04/16 17:11:34 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	add_env_node(t_env **env, const char *str)
{
	t_env	*new;
	t_env	*tmp;
	char	*equal_sign;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return ;

	new->key = ft_strndup(str, equal_sign - str);
	new->value = ft_strdup(equal_sign + 1);
	new->next = NULL;

	if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	init_env(t_env **env, char **envp)
{
	int i = 0;

	while (envp[i])
	{
		add_env_node(env, envp[i]);
		i++;
	}
}
