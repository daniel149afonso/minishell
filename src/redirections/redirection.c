/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/08 02:40:26 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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


int	double_stdout(t_g *g, t_list *redir)
{
	int	fd;

	fd = open((char *)redir->next->content, \
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
		if (double_stdin(tmp, &g->herdoc))
			return (1);
	}
	return (0);
}

int	is_redirection(t_g *g)
{
	t_list	*tmp;

	tmp = g->lst;
	if (parsing_redir(g->lst))
		return (0);
	while (tmp)
	{
		if (check_redirection(g, tmp))
			return (0);
		tmp = tmp->next;
	}
	redirect_in_and__out(g);
	remove_redir_token(&g->lst);
	remove_quotes(&g->lst);
	return (1);
}
