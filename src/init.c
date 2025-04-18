/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:40:58 by apiscopo          #+#    #+#             */
/*   Updated: 2025/04/17 23:06:47 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	init(t_env **env, char **envp, t_envbuilt *envbuilt, t_builtin *builtins)
{
	init_env(env, envp);
	ft_init_commands(envbuilt, builtins);
}