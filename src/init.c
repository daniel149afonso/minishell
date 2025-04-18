/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:40:58 by apiscopo          #+#    #+#             */
/*   Updated: 2025/04/18 16:23:57 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	init(t_g **g, char **envp)
{
	*g = malloc(sizeof(t_g));
	if (!*g)
		return;
	ft_memset(*g, 0, sizeof(t_g));
	init_env(&((*g)->env), envp);
	ft_init_commands((&(*g)->envbuilt), (&(*g)->builtin));
}
