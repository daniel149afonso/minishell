/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 00:32:07 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/15 20:11:47 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_init_commands(t_builtin *builtins)
{
	builtins[0].name = "cd";
	builtins[0].len = strlen("cd");
	builtins[0].f = &ft_cd;
	builtins[1].name = "pwd";
	builtins[1].len = strlen("pwd");
	builtins[1].f = &ft_pwd;
	builtins[2].name = NULL;
	builtins[2].len = 0;
	builtins[2].f = NULL;
	//char	*tab[] = {"cd", "echo", "pwd", "export", "unset", "env", "exit", NULL};
}

void	ft_pwd(t_list *lst)
{
	char	buffer[1024];

	(void)lst;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
		perror("Error, pwd");

}

void	ft_cd(t_list *lst)
{
	int	ret;

	if (!lst->next || !lst->next->content)
	{
		perror("cd: missing argument\n"); //pas vraie erreur sans argument retourne a la racine
		return ;
	}
	ret = chdir((char *)lst->next->content);
	if (ret != 0)
		printf("cd: no such file or directory: %s\n", (char *)lst->next->content);
	else
		printf("Répertoire changé : %s\n", (char *)lst->next->content);
}

int	is_command(t_list *lst, t_builtin *builtins)
{
	t_list	*tmp;
	int		i;

	while (lst)
	{
		tmp = lst->next;
		i = 0;
		while (i < 2)
		{
			if ((ft_strncmp((char *)lst->content, builtins[i].name, builtins[i].len)) == 0)
				builtins[i].f(lst);
			i++;
		}
		lst = tmp;
	}
	return (0);
}

// Function
// {
// 	fd = fork

// 	if pid == 0
// 		while(caca)
// 		{
// 			printf
// 			execve
// 		}

// }

//FT_INIT_COMMANDS:
//init chaque commande avec sa fonction correspondante
//---------------------
//IS_command: check si il y a une commande dans l'input
//et appel la fonction correspondante
