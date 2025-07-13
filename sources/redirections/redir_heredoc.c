/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:20:03 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/13 21:07:52 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Traite << stdin, ouvre un heredoc qui recoit les entrees de l'utilisateur
jusqu'a ce que l'occurence de fermeture soit entre, erreur return 1*/
int	handle_heredoc(t_g *g, char *delimitor, t_env *env, t_redir *redir)
{
	char	*buffer;
	int		pipefd[2];
	char	*expanded;

	(void)g;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	while (1)
	{
		buffer = readline("> ");
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
