/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:09:29 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/21 23:33:34 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	get_current_path(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) == NULL)
		return (0);
	return (1);
}

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

void	ft_cd(t_list *lst)
{
	int		result;
	char	*path;
	char	oldpwd[1024];
	char	newpwd[1024];

	(void)oldpwd;
	(void)newpwd;
	if (lst->next && lst->next->content)
	{
		if (!set_path(lst, &path))
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
		printf("Répertoire changé : %s\n", path);
}
