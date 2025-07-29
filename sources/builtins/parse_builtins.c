/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:18:30 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/29 11:17:54 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*init chaque builtin avec sa fonction correspondante*/
void	init_builtins(t_envbuilt **envbuilt, t_builtin **builtins)
{
	*envbuilt = malloc(sizeof(t_envbuilt) * 4);
	if (!(*envbuilt))
		return ;
	*builtins = malloc(sizeof(t_builtin) * 5);
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
	(*envbuilt)[3].name = NULL;
	(*envbuilt)[3].e = NULL;
}

static int	is_credit(t_cmd *cmd)
{
	if ((ft_strcmp(cmd->argv[0], "credits")) == 0)
	{
		print_credits();
		return (1);
	}
	return (0);
}

static int	builtins_2(t_g *g, t_env *env, t_cmd *cmd, t_envbuilt *envbuilt)
{
	int	i;
	int	code;

	i = 0;
	code = 0;
	while (envbuilt[i].name)
	{
		if (ft_strcmp(cmd->argv[0], envbuilt[i].name) == 0)
		{
			if (redirect_cmd_std(g, cmd) != 0)
				return (1);
			code = envbuilt[i].e(env, g->lst, cmd);
			return_code(env, code);
			return (1);
		}
		i++;
	}
	if (is_credit(cmd))
		return (1);
	return (0);
}

int	builtins(t_g *g, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		if (ft_strchr(cmd->argv[i], '|'))
			return (0);
		i++;
	}
	i = 0;
	if (!cmd->argv || !cmd->argv[0] || !g->env)
		return (0);
	if (builtins_2(g, g->env, cmd, g->envbuilt))
		return (1);
	while (g->builtin[i].name)
	{
		if (ft_strcmp(cmd->argv[0], g->builtin[i].name) == 0)
		{
			if (redirect_cmd_std(g, cmd) != 0)
				return (1);
			return (return_code(g->env, g->builtin[i].f(g, cmd)), 1);
		}
		i++;
	}
	return (0);
}
