/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:40:58 by apiscopo          #+#    #+#             */
/*   Updated: 2025/04/21 23:27:29 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	init_global_struct(t_g **g, char **envp)
{
	*g = malloc(sizeof(t_g));
	if (!*g)
		return ;
	ft_memset(*g, 0, sizeof(t_g));
	init_env(&((*g)->env), envp);
	ft_init_commands((&(*g)->envbuilt), (&(*g)->builtin));
}
