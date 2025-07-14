/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:48:48 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/14 17:46:37 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_pipe(t_list *lst)
{
	while (lst)
	{
		if ((ft_strncmp((char *)lst->content, "|", 1)) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void    free_partial_argv(char **arr, int last_index)
{
    int i = 0;

    while (i < last_index)
        free(arr[i++]);
    free(arr);
}

int	handle_redirection_token(t_list **tmp, t_cmd **curr)
{
	t_list	*redir;

	redir = *tmp;
	if (!redir || !redir->next)
	{
		perror("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (!ft_strcmp(redir->content, "<"))
		store_redirection(*curr, redir->next->content, 1);
	else if (!ft_strcmp(redir->content, ">"))
		store_redirection(*curr, redir->next->content, 2);
	else if (!ft_strcmp(redir->content, ">>"))
		store_redirection(*curr, redir->next->content, 3);
	else if (!ft_strcmp(redir->content, "<<"))
		store_redirection(*curr, redir->next->content, 4);
	*tmp = redir->next->next;
	return (0);
}

t_cmd	*create_command(t_list **lst)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->argv = malloc(sizeof(char *) * 100);
	if (!cmd->argv)
		return (free(cmd), NULL);
	while (*lst && ft_strcmp((*lst)->content, "|") != 0)
	{
		if (is_redirection_token((*lst)->content))
		{
			if (handle_redirection_token(lst, &cmd))
				return (ft_free_all(cmd), NULL);
			continue ;
		}
		cmd->argv[i++] = ft_strdup((*lst)->content);
		*lst = (*lst)->next;
	}
	cmd->argv[i] = NULL;
	return (cmd);
}

t_cmd	*parse_commands(t_list *lst)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*cmd;

	head = NULL;
	curr = NULL;
	cmd = NULL;
	while (lst)
	{
		cmd = create_command(&lst);
		if (!cmd)
			return (free_cmds(head), NULL);
		if (!head)
			head = cmd;
		else
			curr->next = cmd;
		curr = cmd;
		if (lst && ft_strcmp(lst->content, "|") == 0)
			lst = lst->next;
	}
	return (head);
}
