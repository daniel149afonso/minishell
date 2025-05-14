/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/13 20:13:00 by daafonso         ###   ########.fr       */
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
	(*builtins)[3].name = "exit";
	(*builtins)[3].f = &free_n_exit;
	(*builtins)[4].name = NULL;
	(*builtins)[4].f = NULL;
	(*envbuilt)[0].name = "env";
	(*envbuilt)[0].e = &ft_env;
	(*envbuilt)[1].name = "export";
	(*envbuilt)[1].e = &ft_exp;
	(*envbuilt)[2].name = "unset";
	(*envbuilt)[2].e = &f_unset;
}

static int	is_command_2(t_env *env, t_list *lst, t_envbuilt *envbuilt)
{
	t_list	*tmp;
	int		i;

	while (lst)
	{
		tmp = lst->next;
		i = 0;
		while (i < 3)
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
	tmp = g->lst;
	while (tmp)
	{
		i = 0;
		while (i < 4)
		{
			if (is_command_2(g->env, tmp, g->envbuilt))
				return (1);
			if ((ft_strcmp((char *)tmp->content, g->builtin[i].name)) == 0)
			{
				g->builtin[i].f(g);
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
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
