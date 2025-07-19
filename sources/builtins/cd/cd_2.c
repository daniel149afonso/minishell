/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:03:06 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/10 02:07:11 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*Recupere le chemin actuel*/
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

/*Met à jour le chemin vers HOME*/
int	set_home_path(char **path)
{
	*path = getenv("HOME");
	if (!*path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (0);
	}
	return (1);
}

/*Met à jour le chemin et check s'il y a trop d'argument
après la commande CD*/
int	set_path(t_cmd *cmds, char **path)
{
	*path = cmds->argv[1];
	if (cmds->argv && cmds->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (0);
	}
	return (1);
}

/*Met à jour PWD ou OLD_PWD*/
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
