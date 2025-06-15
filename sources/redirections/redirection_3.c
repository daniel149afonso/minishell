/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:15:03 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/15 19:30:39 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Restaure la sortie standard dans le terminal*/
void	restore_std(t_g *g)
{
	if (g->s_stdout != -1)
	{
		dup2(g->s_stdout, STDOUT_FILENO);
		close(g->s_stdout);
	}
	if (g->s_stdin != -1)
	{
		dup2(g->s_stdin, STDIN_FILENO);
		close(g->s_stdin);
	}
}
