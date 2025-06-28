/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:18:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/28 15:19:17 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_redirection_token(char *token)
{
	return (!ft_strcmp(token, "<") || !ft_strcmp(token, ">") ||
			!ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"));
}

int store_stdout_redir(t_cmd *cmd, t_list *redir)
{
	if (!redir || !redir->next || !redir->next->content)
		return (1); // erreur de syntaxe

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

int	redirect_cmd_io(t_g *g, t_cmd *cmd)
{
	int	fd;
	// Redirection d'entrée
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror(cmd->infile);
			return (1);
		}
		g->s_stdin = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	// Redirection de sortie
	if (cmd->outfile)
	{
		int flags = O_WRONLY | O_CREAT | (cmd->append ? O_APPEND : O_TRUNC);
		fd = open(cmd->outfile, flags, 0644);
		if (fd < 0)
		{
			perror(cmd->outfile);
			return (1);
		}
		g->s_stdout = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
