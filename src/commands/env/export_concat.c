/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:11:52 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/04 22:14:58 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*						UTILS						 */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*Permet de extraire la clé de la variable sans le +=*/
char	*extract_key_concat(char *str)
{
	int	i;

	i = 0;
	while ((str[i] && str[i] != '=') && (str[i] != '+' && str[i + 1] != '='))
		i++;
	return (ft_substr(str, 0, i));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*---------------------------
Va rajouter une variable uniquement pour le cas +=
---------------------------*/
void	add_env_node_concat(t_env **env, const char *str)
{
	t_env	*new;
	t_env	*tmp;
	char	*plus_sign;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	plus_sign = ft_strchr(str, '+');
	if (plus_sign)
	{
		new->key = ft_strndup(str, plus_sign - str);
		new->value = ft_strdup(plus_sign + 2);
	}
	else
		new->key = ft_strndup(str, ft_strlen(str));
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
