/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:40:58 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/16 21:07:21 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	update_lvl(t_env *env)
{
	char	*lvl_c;
	int		lvl;

	lvl_c = NULL;
	lvl = 0;
	while (env)
	{
		if ((ft_strncmp(env->key, "SHLVL", 5)) == 0)
		{
			lvl = ft_atoi(env->value);
			lvl_c = ft_itoa(lvl + 1);
			free(env->value);
			env->value = lvl_c;
			break ;
		}
		env = env->next;
	}
}

void	init_global_struct(t_g **g, char **envp)
{
	*g = malloc(sizeof(t_g));
	if (!*g)
		return ;
	ft_memset(*g, 0, sizeof(t_g));
	if (envp)
	{
		init_env(&((*g)->env), envp);
		update_lvl((*g)->env);
	}
	init_builtins((&(*g)->envbuilt), (&(*g)->builtin));
	(*g)->s_stdin = -1;
	(*g)->s_stdout = -1;
	(*g)->prev_fd = -1;
}
