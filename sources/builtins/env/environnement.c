/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:08:37 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/27 04:25:22 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*---------------------------
Fonction appelé au départ du prog 
pour initier un environnement
-----------------------------*/
void	init_env(t_env **env, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		add_env_node(env, envp[i]);
		i++;
	}
}

/*---------------------------
Fonction appelé par l'init pour
ajouter les nodes correspondante a la
copie de l'env original
---------------------------*/
void	add_env_node(t_env **env, const char *str)
{
	t_env	*new;
	t_env	*tmp;
	char	*equal_sign;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		new->key = ft_strndup(str, equal_sign - str);
		new->value = ft_strdup(equal_sign + 1);
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

/*---------------------------
Builtin de la commande env pour
afficher l'environnment comme dans bash
---------------------------*/
int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
