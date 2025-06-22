/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:09:29 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/21 20:23:03 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*Ajoute le chemin de pwd à la variable d'environnement*/
void	add_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
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

/*Check PWD et OLD_PWD met à jour si existe ou
ajoute sinon*/
void	set_env_value(t_env **env, const char *key, const char *value)
{
	if (update_env_if_exists(*env, key, value))
		return ;
	add_env_var(env, key, value);
}

/*Met à jour OLD_PWD*/
int	save_oldpwd(t_env **env, char **oldpwd)
{
	if (!get_current_path(oldpwd))
	{
		perror("cd");
		return (0);
	}
	set_env_value(env, "OLDPWD", *oldpwd);
	return (1);
}

/*Check CD avec arguments = change de dossier,
CD sans argument = HOME*/
int	resolve_path(t_list *lst, char **path)
{
	if (lst->next && lst->next->content)
		return (set_path(lst, path));
	else
		return (set_home_path(path));
}

/*Appel echo qui chande de repertoire tout en modifiant les variables:
OLD_PWD et PWD*/
int	ft_cd(t_g *g)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;
	int		result;

	path = NULL;
	oldpwd = NULL;
	newpwd = NULL;
	if (!save_oldpwd(&g->env, &oldpwd))
		return (1);
	if (!resolve_path(g->lst, &path))
		return (1);
	result = chdir(path);
	if (result != 0)
		return (perror("minishell: cd"), 1);
	else
	{
		if (!get_current_path(&newpwd))
		{
			perror("cd");
			return (1);
		}
		set_env_value(&g->env, "PWD", newpwd);
	}
	return (0);
}
