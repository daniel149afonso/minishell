/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 00:32:07 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/14 23:42:41 by daniel149af      ###   ########.fr       */
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

void	ft_cd(t_list *lst)
{
	int	ret;

	if (!lst->next || !lst->next->content)
	{
		fprintf(stderr, "cd: missing argument\n");
		return;
	}
	ret = chdir((char *)lst->next->content);
	if (ret != 0)
		perror("cd");
	else
		printf("Répertoire changé : %s\n", (char *)lst->next->content);
}


void	ft_echo(void)
{

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
				builtins[i].f(lst);
			i++;
		}
		lst = tmp;
	}
	return (0);
}
//FT_INIT_COMMANDS:
//init chaque commande avec sa fonction correspondante
//---------------------
//IS_command: check si il y a une commande dans l'input
//et appel la fonction correspondante