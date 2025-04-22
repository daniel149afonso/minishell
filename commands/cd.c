/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:09:29 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/22 20:29:39 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	set_home_path(char **path)
{
	*path = getenv("HOME");
	if (!*path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (0);
	}
	printf("Home path: %s\n", *path);
	return (1);
}

int	set_path(t_list *lst, char **path)
{
	*path = (char *)lst->next->content;
	if (lst->next->next)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (0);
	}
	return (1);
}

int	get_current_path(char **path)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (0);
	*path = ft_strdup(buffer);
	if (!*path)
		return (0);
	return (1);
}
void	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*tmp = *env;

	// chercher si la variable existe déjà
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return;
		}
		tmp = tmp->next;
	}
	// sinon on l’ajoute comme une nouvelle
	t_env *new = malloc(sizeof(t_env));
	if (!new)
		return;

	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	// ajouter à la fin
	tmp = *env;
	if (!tmp)
		*env = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}


void	ft_cd(t_g *g)
{
	int		result;
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = NULL;
	newpwd = NULL;
	if (!get_current_path(&oldpwd))
	{
		perror("cd");
		return ;
	}
	printf("Old path:%s\n", oldpwd);
	set_env_value(&g->env, "OLDPWD", oldpwd);
	if (g->lst->next && g->lst->next->content)
	{
		if (!set_path(g->lst, &path))
			return ;
	}
	else
	{
		if (!set_home_path(&path))
			return ;
	}
	result = chdir(path);
	if (result != 0)
		print_path_error(path);
	else
	{
		printf("Répertoire changé : %s\n", path);
		if (!get_current_path(&newpwd))
		{
			perror("cd");
			return ;
		}
		printf("New path:%s\n", newpwd);
		set_env_value(&g->env, "PWD", newpwd);
	}
}
