/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:20:03 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/20 15:22:27 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Traite << stdin, ouvre un heredoc qui recoit les entrees de l'utilisateur
jusqu'a ce que l'occurence de fermeture soit entre, erreur return 1*/
int	handle_heredoc(char *delimitor, t_env *env, int write_fd)
{
	char	*buffer;
	char	*expanded;

	buffer = NULL;
	expanded = NULL;
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
		expanded = expand_variables(buffer, env);
		write(write_fd, expanded, ft_strlen(expanded));
		write(write_fd, "\n", 1);
		free(expanded);
		free(buffer);
	}
	close(write_fd);
	return (0);
}

int	open_all_heredocs(t_g *g, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == 4)
		{
			int pipefd[2];
			if (pipe(pipefd) == -1)
				return (perror("pipe"), 1);
			pid_t pid = fork();
			if (pid == 0)
			{
				close(pipefd[0]);
				handle_heredoc(redir->file, g->env, pipefd[1]);
				exit(0);
			}
			else if (pid > 0)
			{
				close(pipefd[1]);
				redir->heredoc_fd = pipefd[0];
				int status;
				waitpid(pid, &status, 0);
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				{
					write(1, "\n", 1);
					g->interrupted = 1;
					return (1);
				}
			}
			else
				return (perror("fork"), 1);
		}
		redir = redir->next;
	}
	return (0);
}

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
