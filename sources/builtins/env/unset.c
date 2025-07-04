/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:08:41 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/21 20:31:51 by bullestico       ###   ########.fr       */
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
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	f_unset(t_env *env)
{
	t_list	*arg;

	arg = env->lst->next;
	while (arg)
	{
		del_var(env, (char *)arg->content);
		arg = arg->next;
	}
	return (0);
}
