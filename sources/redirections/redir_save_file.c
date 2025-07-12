/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_save_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:18:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/12 15:44:39 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Enregistre chaque redir dans une liste de redirections:
nom de fichier, type de redir*/
void store_redirection(t_cmd *cmd, char *file, int type)
{
	t_redir *new;
	t_redir *last;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->file = ft_strdup(file);
	new->type = type;
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
}
