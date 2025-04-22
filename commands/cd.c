/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:09:29 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/22 17:02:37 by daafonso         ###   ########.fr       */
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
	}

}
