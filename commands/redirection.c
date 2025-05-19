/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/19 01:45:41 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	parsing_redir(t_list *lst)
{
	while (lst)
	{
		if (ft_strcmp((char *)lst->content, ">") == 0 && !lst->next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	remove_token(t_list **lst, t_list **cur, t_list **prev)
{
	t_list	*file;
	t_list	*after;

	file = (*cur)->next;
	after = file->next;
	if (*prev)
		(*prev)->next = after;
	else
		*lst = after;
	free((*cur)->content);
	free(*cur);
	free(file->content);
	free(file);
}

void	remove_redir_token(t_list **lst)
{
	t_list	*curr;
	t_list	*prev;

	curr = *lst;
	prev = NULL;
	while (curr && curr->next)
	{
		if (!ft_strcmp((char *)curr->content, ">") \
		|| !ft_strcmp((char *)curr->content, ">>") \
		|| !ft_strcmp((char *)curr->content, "<"))
		{
			remove_token(lst, &curr, &prev);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	one_stdout(t_g *g, t_list *redir)
{
	int		fd;

	fd = open((char *)redir->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
	// 💾 sauvegarder stdout
	g->s_stdout = dup(STDOUT_FILENO);

	// 🔁 rediriger stdout vers le fichier
	dup2(fd, STDOUT_FILENO);
	close(fd);

	// 🔁 restaurer stdout
	// dup2(original_stdout, STDOUT_FILENO);
	// close(original_stdout);
	return (0);
}

int	double_stdout(t_g *g, t_list *redir)
{
	int		fd;

	fd = open((char *)redir->next->content, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open failed");
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
		perror("open failed");
		return (1);
	}
	g->s_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

void	restore_std(t_g *g)
{
	if (g->s_stdout != -1)
	{
		// 🔁 restaurer stdout
		dup2(g->s_stdout, STDOUT_FILENO);
		close(g->s_stdout);
	}
	if (g->s_stdin != -1)
	{
		// 🔁 restaurer stdin
		dup2(g->s_stdin, STDIN_FILENO);
		close(g->s_stdin);
	}
}

int	is_redirection(t_g *g)
{
	t_list	*tmp;

	tmp = g->lst;
	if (parsing_redir(g->lst))
		return (1);
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->content, ">") == 0)
			one_stdout(g, tmp);
		else if (ft_strcmp((char *)tmp->content, ">>") == 0)
			double_stdout(g, tmp);
		else if (ft_strcmp((char *)tmp->content, "<") == 0)
			one_stdin(g, tmp);
		tmp = tmp->next;
	}
	return (0);
}
