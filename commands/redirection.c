/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/13 15:31:16 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	remove_redir_token(t_list **lst)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*tmp;
	
	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if ((curr)->next && !ft_strcmp((char *)(curr)->next->content, ">"))
		{
			tmp = curr->next;
			free(curr);
			prev->next = tmp;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}	
}

int	one_redirection(t_g *g, t_list *redir)
{
	int		fd;

	fd = open((char *)redir->next->content,
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

int	is_redirection(t_g *g)
{
	t_list	*tmp;

	tmp = g->lst;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->content, ">") == 0)
			one_redirection(g, tmp);
		tmp = tmp->next;
	}
	return (0);
}
