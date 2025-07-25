/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:19:37 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/25 17:28:54 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_free_redir(t_redir *redir)
{
	t_redir	*tmp;

	tmp = NULL;
	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
	redir = NULL;
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
		if (cmds->argv)
		{
			while (cmds->argv[i])
				free(cmds->argv[i++]);
			free(cmds->argv);
		}
		if (cmds->redirections)
			ft_free_redir(cmds->redirections);
		free(cmds);
		cmds = tmp;
	}
	free(cmds);
	cmds = NULL;
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
