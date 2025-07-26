/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:08:37 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/26 12:02:40 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

//Pour le premier check de export
int	is_valid_export_argument(char *str)
{
	int	i;

	if (!str || !ft_isalpha(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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

static void	add_env_node_2(t_env *new, t_env *tmp, t_env **env)
{
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	tmp = NULL;
	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		new->key = ft_strndup(str, equal_sign - str);
		new->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new->key = ft_strndup(str, ft_strlen(str));
		new->value = ft_strdup("");
	}
	new->next = NULL;
	if (!*env)
		*env = new;
	else
		add_env_node_2(new, tmp, env);
}

/*---------------------------
Builtin de la commande env pour
afficher l'environnment comme dans bash
---------------------------*/
int	ft_env(t_env *env, t_list *lst)
{
	t_env	*tmp;

	(void)lst;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
