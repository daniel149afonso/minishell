/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 00:32:07 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/14 00:59:56 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_init_commands(t_builtin *builtins)
{
	builtins[0].name = "cd";
	builtins[0].f = &ft_cd;
	char	*tab[] = {"cd", "echo", "pwd", "export", "unset", "env", "exit", NULL};
}

void	ft_cd(void)
{
	return ;
}

int	is_command(t_list *lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (lst)
	{
		if (strcmp((const char *)lst->content, ))
		{
			
		}
	}
	return (0);
}
