/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:19:37 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/14 23:43:16 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
void	ft_free_redir(t_redir *redir)
{
	t_redir *tmp;

	tmp = NULL;
	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}
void	ft_free_lst(t_list **lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	if (!cmds)
		return ;
	while (cmds)
	{
		i = 0;
		tmp = cmds->next;
		while (cmds->argv[i])
			free(cmds->argv[i++]);
		free(cmds->argv);
		if (cmds->redirections)
			ft_free_redir(cmds->redirections);
		free(cmds);
		cmds = tmp;
	}
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

void	ft_free_all(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_split(cmd->argv);
	ft_free_redir(cmd->redirections);
	free(cmd);
}
