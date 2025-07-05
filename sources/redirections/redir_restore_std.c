/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_restore_std.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:03 by daafonso          #+#    #+#             */
/*   Updated: 2025/07/05 15:05:16 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Traite << stdin, ouvre un heredoc qui recoit les entrees de l'utilisateur
jusqu'a ce que l'occurence de fermeture soit entre, erreur return 1*/
int handle_heredoc(t_g *g, t_cmd *cmd, t_env *env)
{
	char	*buffer;
	int		pipefd[2];
	char	*expanded;
	
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || !ft_strcmp(buffer, cmd->delimitor))
		{
			free(buffer);
			break;
		}
		expanded = expand_variables(buffer, env);
		write(pipefd[1], expanded, ft_strlen(expanded));
		write(pipefd[1], "\n", 1);
		free(expanded);
		free(buffer);
	}
	close(pipefd[1]);
	g->s_stdin = dup(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}
/*Redirige stdin vers un fichier*/
int	redirect_stdin(t_g *g, t_cmd *cmd)
{
	int fd;

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
	return (0);
}
/*Redirige stdout vers un fichier: APPEND ajoute, TRUNC remplace*/
int	redirect_stdout(t_g *g, t_cmd *cmd)
{
	int fd;
	int flags;

	if (cmd->outfile)
	{
		if (cmd->append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
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

/* Redirige stdin ou stdout vers le fichier*/
int redirect_cmd_std(t_g *g, t_cmd *cmd)
{
	t_redir *r = cmd->redirections;
	t_redir *last_out = NULL;

	// Trouver la dernière redirection vers stdout
	for (t_redir *tmp = r; tmp; tmp = tmp->next)
	{
		if (tmp->type == 2 || tmp->type == 3)
			last_out = tmp;
	}

	while (r)
	{
		int fd = -1;

		if (r->type == 1) // <
			fd = open(r->file, O_RDONLY);
		else if (r->type == 2) // >
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == 3) // >>
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);

		if (fd < 0)
		{
			perror(r->file);
			return (1);
		}

		// Seule la dernière redirection applique dup2
		if (r == last_out)
		{
			if (g->s_stdout == -1)
				g->s_stdout = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
		}

		close(fd);
		r = r->next;
	}
	return (0);
}


/*Restaure la sortie standard dans le terminal*/
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