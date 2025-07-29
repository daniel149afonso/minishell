/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:08:41 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/29 11:10:11 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*Deux fonctions qui vont servir à supprimer la valeur 
et la clé d'une variable d'environnment*/
static void	del_var(t_env *env, char *arg)
{
	char	*key;
	t_env	*curr;
	t_env	*prev;

	key = extract_key(arg);
	curr = env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (free(key));
		}
		prev = curr;
		curr = curr->next;
	}
	if (key)
		free(key);
}

int	f_unset(t_env *env, t_list *lst, t_cmd *cmds)
{
	t_list	*arg;

	(void)cmds;
	arg = lst;
	while (arg)
	{
		del_var(env, (char *)arg->content);
		arg = arg->next;
	}
	return (0);
}
