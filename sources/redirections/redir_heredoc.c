/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:20:03 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/22 13:55:21 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Expand variables dans le heredoc*/
void	handle_variable(char *buffer, t_env *env, int write_fd)
{
	char	*expanded;

	expanded = NULL;
	expanded = expand_variables(buffer, env);
	if (!expanded)
	{
		free(expanded);
		free(buffer);
		return ;
	}
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	free(expanded);
	free(buffer);
}

/*Traite << stdin, ouvre un heredoc qui recoit les entrees de l'utilisateur
jusqu'a ce que l'occurence de fermeture soit entre, erreur return 1*/
int	handle_heredoc(char *delimitor, t_env *env, int write_fd)
{
	char	*buffer;

	buffer = NULL;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			close(write_fd);
			exit(130);
		}
		if (!ft_strcmp(buffer, delimitor))
		{
			free(buffer);
			break ;
		}
		handle_variable(buffer, env, write_fd);
	}
	close(write_fd);
	return (0);
}

/*Applique le heredoc dans un processus fils*/
int	open_single_heredoc(t_g *g, t_redir *r)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		close(pipefd[0]);
		handle_heredoc(r->file, g->env, pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	r->heredoc_fd = pipefd[0];
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		g->interrupted = 1;
		return (return_code(g->env, 130), 1);
	}
	return (0);
}

/*Détecte si la redirection est un heredoc*/
int	open_all_heredocs(t_g *g, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == 4)
		{
			if (open_single_heredoc(g, redir) != 0)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

/*Parcourt chaque commande et
applique tous les heredoc de la commande en cours*/
int	collect_heredocs(t_g *g, t_cmd *cmds)
{
	while (cmds)
	{
		if (open_all_heredocs(g, cmds->redirections) != 0)
			return (1);
		cmds = cmds->next;
	}
	return (0);
}
