/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_restore_std.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:03 by daafonso          #+#    #+#             */
/*   Updated: 2025/07/16 20:47:25 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int open_target(char *file, int flags)
{
	int fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
		return (perror(file), 1);
	close(fd);
	return (0);
}

int open_files(t_g *g, t_redir *r)
{
	if (r->type == 1)
		return (open_target(r->file, O_RDONLY));
	else if (r->type == 2)
		return (open_target(r->file, O_WRONLY | O_CREAT | O_TRUNC));
	else if (r->type == 3)
		return (open_target(r->file, O_WRONLY | O_CREAT | O_APPEND));
	else if (r->type == 4)
	{
		if (g->s_stdin == -1)
			g->s_stdin = dup(STDIN_FILENO);
		if (handle_heredoc(g, r->file, g->env, r) != 0)
			return (1);
	}
    return (0);
}

int prepare_redirections(t_g *g, t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirections;
	while (r)
	{
		if (open_files(g, r))
			return (1);
		r = r->next;
	}
	return (0);
}

int	apply_last_redir(t_g *g, t_redir *r, t_redir *last_in, t_redir *last_out)
{
	int fd = -1;

		if (r == last_in && r->type == 1)
		{
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
				return (perror(r->file), 1);
			g->s_stdin = dup(STDIN_FILENO);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (r == last_out)
		{
			if (r->type == 2)
				fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (r->type == 3)
				fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(r->file), 1);
			g->s_stdout = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	return (0);
}

int	apply_redirections(t_g *g, t_cmd *cmd)
{
	t_redir *r;
	t_redir *last_in = NULL;
	t_redir *last_out = NULL;

	r = cmd->redirections;
	while (r)
	{
		if (r->type == 1 || r->type == 4)
			last_in = r;
		if (r->type == 2 || r->type == 3)
			last_out = r;
		r = r->next;
	}
	r = cmd->redirections;
	while (r)
	{
		if (apply_last_redir(g, r, last_in, last_out))
			return (1);
		r = r->next;
	}
	return (0);
}

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