/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:48:48 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/23 15:32:08 by daniel149af      ###   ########.fr       */
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

t_cmd	*create_new_cmd(char **args)
{
	t_cmd *new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = args;
	new->infile = NULL;
	new->outfile = NULL;
	new->append = 0;
	new->next = NULL;
	return (new);
}

int	handle_pipe_token(t_cmd **head, t_cmd **curr, char ***args, int *i)
{
	(*args)[*i] = NULL;
	t_cmd *new = create_new_cmd(*args);
	if (!new)
		return (-1);
	if (!*head)
		*head = new;
	else
		(*curr)->next = new;
	*curr = new;
	*args = malloc(sizeof(char *) * 100);
	if (!*args)
		return (-1);
	*i = 0;
	return (0);
}

int	handle_redirection_token(t_list **tmp, t_cmd *cmd)
{
	t_list *redir = *tmp;

	if (!redir || !redir->next)
		return (1); // erreur de syntaxe

	if (!ft_strcmp(redir->content, "<"))
		return (store_stdin_redir(cmd, redir)), *tmp = redir->next->next, 0;
	else if (!ft_strcmp(redir->content, ">"))
		return (store_stdout_redir(cmd, redir)), *tmp = redir->next->next, 0;
	else if (!ft_strcmp(redir->content, ">>"))
		return (store_append_redir(cmd, redir)), *tmp = redir->next->next, 0;

	// Pour l’instant, on ignore `<<`
	return (0);
}

t_cmd	*parse_commands(t_list *lst)
{
	t_cmd	*head = NULL;
	t_cmd	*curr = NULL;
	char	**args = malloc(sizeof(char *) * 100);
	int		i = 0;
	t_list	*tmp = lst;

	while (tmp)
	{
		if (!ft_strcmp(tmp->content, "|"))
		{
			if (handle_pipe_token(&head, &curr, &args, &i) == -1)
				return (NULL);
			tmp = tmp->next;
			continue;
		}
		else if (is_redirection_token(tmp->content))
		{
			if (handle_redirection_token(&tmp, curr))
				return (NULL);
			continue;
		}
		args[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}

	if (i > 0 || !curr)
	{
		args[i] = NULL;
		t_cmd *new = create_new_cmd(args);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
			curr->next = new;
	}
	else
		free(args);
	return (head);
}


// int	new_commmand(t_cmd **head, t_cmd **curr, t_list *tmp, char ***args, int i)
// {
// 	t_cmd	*new;

// 	if (ft_strcmp(tmp->content, "|") == 0)
// 	{
// 		(*args)[i] = NULL;
// 		new = malloc(sizeof(t_cmd));
// 		if (!new)
// 			return (-1);
// 		new->argv = *args;
// 		new->next = NULL;
// 		if (!*head)
// 			*head = new;
// 		else
// 			(*curr)->next = new;
// 		*curr = new;
// 		*args = malloc(sizeof(char *) * 100);
// 		return (0);
// 	}
// 	else
// 		(*args)[i++] = ft_strdup(tmp->content);
// 	return (i);
// }

// void	last_command(t_cmd **head, t_cmd **curr, char **args, int i)
// {
// 	t_cmd	*new;

// 	new = malloc(sizeof(t_cmd));
// 	if (!new)
// 		return ;
// 	new->argv = args;
// 	new->next = NULL;
// 	args[i] = NULL;
// 	if (!*head)
// 		*head = new;
// 	else
// 		(*curr)->next = new;
// 	*curr = new;
// }

// /*Va créer une nouvelle liste appelé cmd pour parser les commandes
// externes avec leurs arguments*/
// t_cmd	*parse_commands(t_list *lst)
// {
// 	t_cmd	*head;
// 	t_cmd	*curr;
// 	t_list	*tmp;
// 	char	**args;
// 	int		i;

// 	head = NULL;
// 	curr = NULL;
// 	tmp = lst;
// 	args = malloc(sizeof(char *) * 100);
// 	i = 0;
// 	while (tmp)
// 	{
// 		i = new_commmand(&head, &curr, tmp, &args, i);
// 		if (i == -1)
// 			return (NULL);
// 		tmp = tmp->next;
// 	}
// 	last_command(&head, &curr, args, i);
// 	return (head);
// }
