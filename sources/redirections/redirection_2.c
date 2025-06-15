/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:03 by daafonso          #+#    #+#             */
/*   Updated: 2025/06/15 18:55:57 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Traite << stdin, ouvre un heredoc qui recoit les entrees de l'utilisateur
jusqu'a ce que l'occurence de fermeture soit entre, erreur return 1*/
int	double_stdin(t_list *redir, t_list **heredoc, t_env *env, int turn)
{
	char	*occur;
	char	*buffer;

	buffer = ft_calloc(1, 1);
	if (!buffer)
		return (1);
	occur = ((char *)redir->next->content);
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
		{
			if (!ft_strcmp(buffer, occur))
				break ;
			if (turn)
				*heredoc = ft_lstnew(expand_variables(ft_strdup(buffer), env));
			else
				ft_lstadd_back(heredoc,
					ft_lstnew(expand_variables(ft_strdup(buffer), env)));
			turn = 0;
		}
		free(buffer);
	}
	return (0);
}

void	redirect_std_to_file(t_g *g)
{
	if (g->fd_stdout != -1)
	{
		dup2(g->fd_stdout, STDOUT_FILENO);
		close(g->fd_stdout);
		g->fd_stdout = -1;
	}
	if (g->fd_stdin != -1)
	{
		dup2(g->fd_stdin, STDIN_FILENO);
		close(g->fd_stdin);
		g->fd_stdin = -1;
	}
}

void	apply_redirections(t_g *g)
{
	if (g->fd_stdout != -1)
	{
		g->s_stdout = dup(STDOUT_FILENO);
		dup2(g->fd_stdout, STDOUT_FILENO);
		close(g->fd_stdout);
		g->fd_stdout = -1;
	}
	if (g->fd_stdin != -1)
	{
		g->s_stdin = dup(STDIN_FILENO);
		dup2(g->fd_stdin, STDIN_FILENO);
		close(g->fd_stdin);
		g->fd_stdin = -1;
	}
}

void	remove_redir_token_2(t_list **lst, t_list **cur, t_list **prev)
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
	*cur = after;
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
		|| !ft_strcmp((char *)curr->content, "<") \
		|| !ft_strcmp((char *)curr->content, "<<"))
		{
			remove_redir_token_2(lst, &curr, &prev);
			continue ;
		}
		prev = curr;
		curr = curr->next;
	}
}
