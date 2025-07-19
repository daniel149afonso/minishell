/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:20:03 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/18 16:05:04 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Traite << stdin, ouvre un heredoc qui recoit les entrees de l'utilisateur
jusqu'a ce que l'occurence de fermeture soit entre, erreur return 1*/
// int	handle_heredoc(t_g *g, char *delimitor, t_env *env, t_redir *redir)
// {
// 	char	*buffer;
// 	int		pipefd[2];
// 	char	*expanded;

// 	(void)g;
// 	if (pipe(pipefd) == -1)
// 		return (perror("pipe"), 1);
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// 	while (1)
// 	{
// 		buffer = readline("> ");
// 		if (!buffer || !ft_strcmp(buffer, delimitor))
// 		{
// 			free(buffer);
// 			break ;
// 		}
// 		expanded = expand_variables(buffer, env);
// 		write(pipefd[1], expanded, ft_strlen(expanded));
// 		write(pipefd[1], "\n", 1);
// 		free(expanded);
// 		free(buffer);
// 	}
// 	close(pipefd[1]);
// 	redir->heredoc_fd = pipefd[0];
// 	return (0);
// }

int	handle_heredoc(t_g *g, char *delimitor, t_env *env, t_redir *redir)
{
	char	*buffer;
	int		pipefd[2];
	char	*expanded;

	(void)g;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			// Ctrl-C ou EOF → exit avec code 130
			close(pipefd[1]);
			close(pipefd[0]);
			exit(130); // convention POSIX pour interruption par SIGINT
		}
		if (!buffer || !ft_strcmp(buffer, delimitor))
		{
			free(buffer);
			break ;
		}
		expanded = expand_variables(buffer, env);
		write(pipefd[1], expanded, ft_strlen(expanded));
		write(pipefd[1], "\n", 1);
		free(expanded);
		free(buffer);
	}
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (0);
}

int open_all_heredocs(t_g *g, t_redir *redir)
{
    while (redir)
    {
        if (redir->type == 4)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                signal(SIGINT, SIG_DFL);
                exit(handle_heredoc(g, redir->file, g->env, redir));
            }
            else if (pid > 0)
            {
                int status;
                waitpid(pid, &status, 0);
				if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
				{
					write(1, "\n", 1); // retour à la ligne propre
					g->interrupted = 1; // tu peux ajouter ce champ dans ta struct globale
					return (1); // signaler que l'exécution doit être annulée
				}
                if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
                    return (1);
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
