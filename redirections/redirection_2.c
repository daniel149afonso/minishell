/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:03 by daafonso          #+#    #+#             */
/*   Updated: 2025/05/20 18:48:14 by daafonso         ###   ########.fr       */
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
