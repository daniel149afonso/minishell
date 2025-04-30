/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
<<<<<<< HEAD
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/27 19:25:03 by daniel149af      ###   ########.fr       */
=======
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/18 18:51:57 by apiscopo         ###   ########.fr       */
>>>>>>> a57701459356786b47e5323297c800ddc37f4047
=======
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/29 19:40:34 by daniel149af      ###   ########.fr       */
>>>>>>> 981d5bb1b09e6477ae51ed541e0ba43197973ffe
/*                                                                            */
/* ************************************************************************** */


#include "../header/minishell.h"

void	ft_init_commands(t_envbuilt **envbuilt, t_builtin **builtins)
{
	*envbuilt = malloc(sizeof(t_envbuilt) * 5);
	if (!(*envbuilt))
		return ;
	*builtins = malloc(sizeof(t_builtin) * 8);
	if (!(*builtins))
		return ;
	(*builtins)[0].name = "cd";
	(*builtins)[0].f = &ft_cd;
	(*builtins)[1].name = "pwd";
	(*builtins)[1].f = &ft_pwd;
	(*builtins)[2].name = "echo";
	(*builtins)[2].f = &ft_echo;
	(*builtins)[3].name = NULL;
	(*builtins)[3].f = NULL;
	(*envbuilt)[0].name = "env";
	(*envbuilt)[0].e = &ft_env;
	(*envbuilt)[1].name = "export";
	(*envbuilt)[1].e = &ft_exp;
}

<<<<<<< HEAD
<<<<<<< HEAD
void	ft_exp(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!env->lst->next)
	{
		while (tmp)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"\n", tmp->value);
			tmp = tmp->next;
		}
	}
=======
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
	int		result;
	char	*path;

	if (lst->next && lst->next->content)
	{
		path = (char *)lst->next->content;
		if (lst->next->next)
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			return ;
		}
	}
	else
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		printf("Home path: %s\n", path);
	}
	result = chdir(path);
	if (result != 0)
		print_path_error(path);
	else
		printf("Répertoire changé : %s\n", path);
}

void	ft_echo(t_list *lst)
{
	(void)lst;
>>>>>>> a57701459356786b47e5323297c800ddc37f4047
	return ;
}

=======
>>>>>>> 981d5bb1b09e6477ae51ed541e0ba43197973ffe
void	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static int	is_command_2(t_env *env, t_list *lst, t_envbuilt *envbuilt)
{
	t_list	*tmp;
	int		i;

	while (lst)
	{
		tmp = lst->next;
		i = 0;
		while (i < 2)
		{
			if (ft_strcmp((char *)lst->content, envbuilt[i].name) == 0)
			{
				envbuilt[i].e(env);
				return (1);
			}
			i++;
		}
		lst = tmp;
	}
	return (0);
}

int	is_command(t_g *g)
{
	t_list	*tmp;
	int		i;

	g->env->lst = g->lst;
	while (g->lst)
	{
		tmp = g->lst->next;
		i = 0;
		while (i < 3)
		{
			if (is_command_2(g->env, g->lst, g->envbuilt))
				return (1);
			if ((ft_strcmp((char *)g->lst->content, g->builtin[i].name)) == 0)
			{
				g->builtin[i].f(g);
				return (1);
			}
			i++;
		}
		g->lst = tmp;
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
