/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:18:30 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/21 20:43:27 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*init chaque builtin avec sa fonction correspondante*/
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
	int		code;

	code = 0;
	while (lst)
	{
		tmp = lst->next;
		i = 0;
		while (i < 3)
		{
			if (ft_strcmp((char *)lst->content, envbuilt[i].name) == 0)
			{
				code = envbuilt[i].e(env);
				return_code(env, code);
				return (1);
			}
			i++;
		}
		lst = tmp;
	}
	return (0);
}

/*Check s'il y a une builtin dans la commande
puis appelle sa fonction correspondante
et applique les redirections si besoin*/
int	is_command(t_g *g)
{
	t_list	*tmp;
	int		i;
	int		code;

	g->env->lst = g->lst;
	tmp = g->lst;
	code = 0;
	apply_redirections(g);
	while (tmp)
	{
		i = 0;
		while (i < 4)
		{
			if (is_command_2(g->env, tmp, g->envbuilt))
				return (1);
			if ((ft_strcmp((char *)tmp->content, g->builtin[i].name)) == 0)
			{
				code = g->builtin[i].f(g);
				return (return_code(g->env, code), 1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
