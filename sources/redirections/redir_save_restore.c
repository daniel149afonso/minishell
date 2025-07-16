/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_save_restore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:18:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/16 20:55:30 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Enregistre chaque redir dans une liste de redirections:
nom de fichier, type de redir*/
int	store_redirection(t_cmd *cmd, char *file, int type)
{
	t_redir	*new;
	t_redir	*last;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (1);
	new->file = ft_strdup(file);
	if (!new->file)
		return (free(new), 1);
	new->type = type;
	new->heredoc_fd = -1;
	new->next = NULL;
	last = cmd->redirections;
	if (!last)
		cmd->redirections = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (0);
}
/*Prepare (ouvre tous les fichiers) et applique les redirections*/
int	redirect_cmd_std(t_g *g, t_cmd *cmd)
{
	if (prepare_redirections(g, cmd) != 0)
		return (1);
	if (apply_redirections(g, cmd) != 0)
		return (1);
	return (0);
}
/*Restaure la sortie et l'entrée standard dans le terminal*/
void	restore_std(t_g *g)
{
	if (g->s_stdout != -1)
	{
		dup2(g->s_stdout, STDOUT_FILENO);
		close(g->s_stdout);
		g->s_stdout = -1;
	}
	if (g->s_stdin != -1)
	{
		dup2(g->s_stdin, STDIN_FILENO);
		close(g->s_stdin);
		g->s_stdin = -1;
	}
}