/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/24 18:19:27 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	one_stdout(t_g *g, t_list *redir)
{
	int		fd;

	fd = open((char *)redir->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s: No such file or directory\n", (char *)redir->next->content);
		return (1);
	}
	// 💾 sauvegarder stdout
	g->s_stdout = dup(STDOUT_FILENO);
	// 🔁 rediriger stdout vers le fichier
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	double_stdout(t_g *g, t_list *redir)
{
	int		fd;

	fd = open((char *)redir->next->content, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("%s: No such file or directory\n", (char *)redir->next->content);
		return (1);
	}
	g->s_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
	g->s_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	double_stdin(t_list *redir, t_list **herdoc)
{
	char	*occur;
	char	*buffer;
	int		turn;

	buffer = ft_calloc(1, 1);
	if (!buffer)
		return (1);
	turn = 1;
	occur = ((char *)redir->next->content);
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
		{
			if (!ft_strcmp(buffer, occur))
				break ;
			if (turn)
				*herdoc = ft_lstnew(ft_strdup(buffer));
			else
				ft_lstadd_back(herdoc, ft_lstnew(ft_strdup(buffer)));
			turn = 0;
		}
		free(buffer);
	}
	return (0);
}

int	check_redirection(t_g *g, t_list *tmp)
{
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
	return (1);
}
