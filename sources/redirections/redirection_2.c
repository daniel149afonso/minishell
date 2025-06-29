/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:03 by daafonso          #+#    #+#             */
/*   Updated: 2025/06/29 18:41:31 by daniel149af      ###   ########.fr       */
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
		//Enlever condition ternaire!!!!
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
	if (cmd->heredoc)
	{
		
	}
	
	return (0);
}

// int	redirect_stdout(t_g *g, t_cmd *cmd)
// {
	
	
// 	return (0);
// }

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