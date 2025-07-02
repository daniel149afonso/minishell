/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:03 by daafonso          #+#    #+#             */
/*   Updated: 2025/07/02 19:09:25 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Traite << stdin, ouvre un heredoc qui recoit les entrees de l'utilisateur
jusqu'a ce que l'occurence de fermeture soit entre, erreur return 1*/
int	double_stdin(t_cmd *cmd, t_env *env)
{
	char	*buffer;
	int		i;

	i = 0;
	cmd->text = malloc(sizeof(char *) * 100);
	if (!cmd->text)
		return (1);
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
		{
			if (!ft_strcmp(buffer, (char *)cmd->delimitor))
			{
				free(buffer);
				break ;
			}
			cmd->text[i] = expand_variables(ft_strdup(buffer), env);
			i++;
			free(buffer);  // Ici UNIQUEMENT
		}
	}
	cmd->text[i] = NULL;
	//ft_print_array(cmd->text);
	return (0);
}
/* Redirige stdin ou stdout en fonction 
*/
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
	//Pas encore fini
	if (cmd->heredoc)
	{
		if (double_stdin(cmd, g->env) == 1)
			return (1);
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