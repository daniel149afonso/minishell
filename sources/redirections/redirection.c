/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/23 15:56:17 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Traite > stdout pour ajouter le contenu dans le fichier
(le contenu existant dans le fichier est ecrase), si une erreur return 1*/
int	one_stdout(t_g *g, t_list *redir)
{
	int	fd;

	fd = open((char *)redir->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s: No such file or directory\n", (char *)redir->next->content);
		return (1);
	}
	if (g->fd_stdout != -1)
		close(g->fd_stdout);
	g->fd_stdout = fd;
	return (0);
}

/*Traite >> stdout pour ajouter a la suite du fichier, si une erreur return 1*/
int	double_stdout(t_g *g, t_list *redir)
{
	int	fd;

	fd = open((char *)redir->next->content,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("%s: No such file or directory\n", (char *)redir->next->content);
		return (1);
	}
	if (g->fd_stdout != -1)
		close(g->fd_stdout);
	g->fd_stdout = fd;
	return (0);
}

/*Traite < stdin dirige le contenu d'un fichier vers stdin,
si erreur return 1*/
int	one_stdin(t_g *g, t_list *redir)
{
	int		fd;

	fd = open((char *)redir->next->content, O_RDONLY, 0644);
	if (fd < 0)
	{
		printf("%s: No such file or directory\n", (char *)redir->next->content);
		return (1);
	}
	if (g->fd_stdin != -1)
		close(g->fd_stdin);
	g->fd_stdin = fd;
	return (0);
}

/*Cherche le type de redirection si une erreur return 1*/
int	check_redirection(t_g *g, t_list *tmp)
{
	if (check_quotes((char *)tmp->content))
		return (0);
	if (ft_strcmp((char *)tmp->content, ">") == 0)
	{
		if (one_stdout(g, tmp))
			return (1);
	}
	else if (ft_strcmp((char *)tmp->content, ">>") == 0)
	{
		if (double_stdout(g, tmp))
			return (1);
	}
	else if (ft_strcmp((char *)tmp->content, "<") == 0)
	{
		if (one_stdin(g, tmp))
			return (1);
	}
	else if (ft_strcmp((char *)tmp->content, "<<") == 0)
	{
		if (double_stdin(tmp, &g->heredoc, g->env))
			return (1);
	}
	return (0);
}

int	validate_redirection_syntax(t_list *lst)
{
	if (parsing_redir(lst))
		return (0);
	return (1);
}

// /*Cherche une redirection si une erreur return 0*/
// int	is_redirection(t_g *g)
// {
// 	t_list	*tmp;

// 	tmp = g->lst;
// 	if (parsing_redir(g->lst))
// 		return (0);
// 	//Parse command commence là!!!!!!!!!!
// 	while (tmp)
// 	{
// 		if (check_redirection(g, tmp))
// 			return (0);
// 		tmp = tmp->next;
// 	}
// 	remove_redir_token(&g->lst);
// 	remove_quotes(&g->lst);
// 	return (1);
// }
// int is_redirection(t_g *g)
// {
//     t_list *tmp = g->lst;
//     int      idx = 0;

//     // parcourir toute la ligne tant qu'on n'a pas trouvé > ou <
//     while (tmp)
//     {
//         if (check_redirection(g, tmp))  // ton test existant
//         {
//             g->redir_cmd_idx = idx;
//             break;
//         }
//         if (strcmp((char*)tmp->content, "|") == 0)
//             idx++;
//         tmp = tmp->next;
//     }

//     // ton code existant de parsing_redir / remove_redir_token...
//     if (parsing_redir(g->lst))
//         return (0);
//     tmp = g->lst;
//     while (tmp)
//     {
//         if (check_redirection(g, tmp))
//             return (0);
//         tmp = tmp->next;
//     }
//     remove_redir_token(&g->lst);
//     remove_quotes(&g->lst);
//     return (1);
// }