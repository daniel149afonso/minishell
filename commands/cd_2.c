/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:03:06 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/28 16:25:50 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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