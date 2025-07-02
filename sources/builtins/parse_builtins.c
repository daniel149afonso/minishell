/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:18:30 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/02 18:52:59 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*init chaque builtin avec sa fonction correspondante*/
void	init_builtins(t_envbuilt **envbuilt, t_builtin **builtins)
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

static int	builtins_2(t_env *env, t_cmd *cmd, t_envbuilt *envbuilt)
{
	int	i;
	int	code;

	if (!cmd->argv || !cmd->argv[0])
		return (0);
	i = 0;
	code = 0;
	while (envbuilt[i].name)
	{
		if (ft_strcmp(cmd->argv[0], envbuilt[i].name) == 0)
		{
			code = envbuilt[i].e(env);
			return_code(env, code);
			return (1);
		}
		i++;
	}
	return (0);
}

int builtins(t_g *g, t_cmd *cmd)
{
	int	i;
	int	code;

	if (builtins_2(g->env, cmd, g->envbuilt))
		return (1);
	i = 0;
	code = 0;
	while (g->builtin[i].name)
	{
		if (ft_strcmp(cmd->argv[0], g->builtin[i].name) == 0)
		{
			if (redirect_cmd_io(g, cmd) != 0)
				return (1);
			code = g->builtin[i].f(g, cmd);
			return_code(g->env, code);
			return (1);
		}
		i++;
	}
	return (0);
}
