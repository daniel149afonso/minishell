/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:18:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/04 16:21:45 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int store_stdout_redir(t_cmd *cmd, t_list *redir)
{
	if (!redir || !redir->next || !redir->next->content)
		return (1);

	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup((char *)redir->next->content);
	cmd->append = 0;
	return (0);
}

int store_append_redir(t_cmd *cmd, t_list *redir)
{
	if (!redir || !redir->next || !redir->next->content)
		return (1);

	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup((char *)redir->next->content);
	cmd->append = 1;
	return (0);
}

int store_stdin_redir(t_cmd *cmd, t_list *redir)
{
	if (!redir || !redir->next || !redir->next->content)
		return (1);

	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup((char *)redir->next->content);
	return (0);
}

int store_heredoc_redir(t_cmd *cmd, t_list *redir)
{
	if (!redir || !redir->next || !redir->next->content)
		return (1);

	if (cmd->delimitor)
		free(cmd->delimitor);
	cmd->delimitor = ft_strdup((char *)redir->next->content);
	cmd->heredoc = 1;
	return (0);
}

