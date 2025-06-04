/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:09:29 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/30 18:34:15 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void	set_env_value(t_env **env, const char *key, const char *value)
{
	if (update_env_if_exists(*env, key, value))
		return ;
	add_env_var(env, key, value);
}

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

int	resolve_path(t_list *lst, char **path)
{
	if (lst->next && lst->next->content)
		return (set_path(lst, path));
	else
		return (set_home_path(path));
}

void	ft_cd(t_g *g)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;
	int		result;

	path = NULL;
	oldpwd = NULL;
	newpwd = NULL;
	if (!save_oldpwd(&g->env, &oldpwd))
		return ;
	if (!resolve_path(g->lst, &path))
		return ;
	result = chdir(path);
	if (result != 0)
		perror("minishell: cd");
	else
	{
		if (!get_current_path(&newpwd))
		{
			perror("cd");
			return ;
		}
		set_env_value(&g->env, "PWD", newpwd);
	}
}
