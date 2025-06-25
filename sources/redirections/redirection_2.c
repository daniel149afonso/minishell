/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:03 by daafonso          #+#    #+#             */
/*   Updated: 2025/06/25 17:54:09 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Traite << stdin, ouvre un heredoc qui recoit les entrees de l'utilisateur
jusqu'a ce que l'occurence de fermeture soit entre, erreur return 1*/
int	double_stdin(t_list *redir, t_list **heredoc, t_env *env)
{
	char	*occur;
	char	*buffer;

	occur = ((char *)redir->next->content);
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
		{
			if (!ft_strcmp(buffer, occur))
			{
				free(buffer);
				break ;
			}
			if (!*heredoc)
				*heredoc = ft_lstnew(expand_variables(ft_strdup(buffer), env));
			else
				ft_lstadd_back(heredoc,
					ft_lstnew(expand_variables(ft_strdup(buffer), env)));
			free(buffer);  // Ici UNIQUEMENT
		}
		else
			break ; // readline retourne NULL (CTRL+D)
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
	}
	if (g->s_stdin != -1)
	{
		dup2(g->s_stdin, STDIN_FILENO);
		close(g->s_stdin);
	}
}