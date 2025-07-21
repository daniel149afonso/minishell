/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:03 by daafonso          #+#    #+#             */
/*   Updated: 2025/07/21 01:49:46 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Ouvre le fichier*/
int	open_target(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
		return (perror(file), 1);
	close(fd);
	return (0);
}

/*Ouvre le fichier avec les bons flags*/
int	open_files(t_g *g, t_redir *r)
{
	(void)g;
	if (r->type == 1)
		return (open_target(r->file, O_RDONLY));
	else if (r->type == 2)
		return (open_target(r->file, O_WRONLY | O_CREAT | O_TRUNC));
	else if (r->type == 3)
		return (open_target(r->file, O_WRONLY | O_CREAT | O_APPEND));
	else if (r->type == 4)
	{
		return (0);
		// if (g->s_stdin == -1)
		// 	g->s_stdin = dup(STDIN_FILENO);
		// if (handle_heredoc(g, r->file, g->env, r) != 0)
		// 	return (1);
	}
	return (0);
}

/*Ouvre tous les fichiers sans rediriger les stdin stdout*/
int	prepare_redirections(t_g *g, t_cmd *cmd)
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

/*Redirige l'entrée ou la sortie vers le dernier fichier*/
int	apply_last_redir(t_g *g, t_redir *r, t_redir *last_in, t_redir *last_out)
{
	int	fd;

	fd = -1;
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
	t_redir	*r;
	t_redir	*last_in;
	t_redir	*last_out;

	last_in = NULL;
	last_out = NULL;
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
