/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 00:32:07 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/14 19:48:11 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_init_commands(t_builtin *builtins)
{
	builtins[0].name = "cd";
	builtins[0].f = &ft_cd;
	builtins[1].name = NULL;
	builtins[1].f = NULL;
	//char	*tab[] = {"cd", "echo", "pwd", "export", "unset", "env", "exit", NULL};
}

void	ft_cd(void)
{
	printf("Hello command cd\n");
	return ;
}

int	is_command(t_list *lst, t_builtin *builtins)
{
	t_list	*tmp;
	int		i;

	while (lst)
	{
		tmp = lst->next;
		i = 0;
		while (i < 1)
		{
			if ((ft_strncmp((char *)lst->content, builtins[i].name, 2)) == 0)
				builtins[i].f();
			i++;
		}
		lst = tmp;
	}
	return (0);
}
