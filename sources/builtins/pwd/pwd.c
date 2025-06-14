/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:10:10 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/14 20:32:19 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*Recupere le chemin actuel et l'affiche*/
void	ft_pwd(t_g *g)
{
	char	buffer[1024];

	(void)g;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
	{
		perror("Error, pwd");
		return (return_code(g->env, 1));
	}
	return (return_code(g->env, 0));
}
