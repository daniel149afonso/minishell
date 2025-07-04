/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_save_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:18:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/05 15:04:31 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void store_redirection(t_cmd *cmd, char *file, int type)
{
	t_redir *new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->file = ft_strdup(file);
	new->type = type;
	new->next = NULL;

	t_redir *last = cmd->redirections;
	if (!last)
		cmd->redirections = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}


