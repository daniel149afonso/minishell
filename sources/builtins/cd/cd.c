/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:09:29 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/14 23:57:35 by daniel149af      ###   ########.fr       */
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
static void	set_env_value(t_env **env, char *key, char *value)
{
	if (update_env_if_exists(*env, key, value))
		return ;
	add_env_var(env, (const char *)key, (const char *)value);
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
int	resolve_path(t_cmd *cmds, char **path)
{
	if (cmds->argv && cmds->argv[1])
		return (set_path(cmds, path));
	else
		return (set_home_path(path));
}

/*Appel echo qui chande de repertoire tout en modifiant les variables:
OLD_PWD et PWD*/
int	ft_cd(t_g *g, t_cmd *cmds)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;
	int		result;

	path = NULL;
	oldpwd = NULL;
	newpwd = NULL;
	if (!save_oldpwd(&g->env, &oldpwd))
		return (free(oldpwd), 1);
	if (!resolve_path(cmds, &path))
		return (free(oldpwd), 1);
	result = chdir(path);
	if (result != 0)
		return (perror("minishell: cd"), free(oldpwd), 1);
	else
	{
		if (!get_current_path(&newpwd))
			return (perror("cd"), free(oldpwd), 1);
		set_env_value(&g->env, "PWD", newpwd);
	}
	return (free(newpwd), free(oldpwd), 0);
}
