/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:03 by daafonso          #+#    #+#             */
/*   Updated: 2025/05/21 17:02:47 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
		|| !ft_strcmp((char *)curr->content, "<") \
		|| !ft_strcmp((char *)curr->content, "<<"))
		{
			remove_token(lst, &curr, &prev);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}
