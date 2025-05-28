/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:09:29 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/28 16:32:19 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	update_env_if_exists(t_env *env, const char *key, const char *value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

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
		print_path_error(path);
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

// void	ft_cd(t_g *g)
// {
// 	int		result;
// 	char	*path;
// 	char	*oldpwd;
// 	char	*newpwd;

// 	oldpwd = NULL;
// 	newpwd = NULL;
// 	if (!get_current_path(&oldpwd))
// 	{
// 		perror("cd");
// 		return ;
// 	}
// 	printf("Old path:%s\n", oldpwd);
// 	set_env_value(&g->env, "OLDPWD", oldpwd);
// 	if (g->lst->next && g->lst->next->content)
// 	{
// 		if (!set_path(g->lst, &path))
// 			return ;
// 	}
// 	else
// 	{
// 		if (!set_home_path(&path))
// 			return ;
// 	}
// 	result = chdir(path);
// 	if (result != 0)
// 		print_path_error(path);
// 	else
// 	{
// 		printf("Répertoire changé : %s\n", path);
// 		if (!get_current_path(&newpwd))
// 		{
// 			perror("cd");
// 			return ;
// 		}
// 		printf("New path:%s\n", newpwd);
// 		set_env_value(&g->env, "PWD", newpwd);
// 	}
// }
