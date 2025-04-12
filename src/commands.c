/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 00:32:07 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/12 00:46:38 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_init_commands(t_command *commands)
{
	
	commands->tab = ["cd", "echo", "pwd", "export", "unset", "env", "exit"];
}

int	is_command(t_list *lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (lst)
	{
		if (strcmp((const char *)lst->content, ))
	}
	return (0);
}