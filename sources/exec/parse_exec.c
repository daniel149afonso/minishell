/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:48:48 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/15 19:42:20 by apiscopo         ###   ########.fr       */
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

int	new_commmand(t_cmd **head, t_cmd **curr, t_list *tmp, char ***args, int i)
{
	t_cmd	*new;

	if (ft_strcmp(tmp->content, "|") == 0)
	{
		(*args)[i] = NULL;
		new = malloc(sizeof(t_cmd));
		if (!new)
			return (-1);
		new->argv = *args;
		new->next = NULL;
		if (!*head)
			*head = new;
		else
			(*curr)->next = new;
		*curr = new;
		*args = malloc(sizeof(char *) * 100);
		return (0);
	}
	else
		(*args)[i++] = ft_strdup(tmp->content);
	return (i);
}

void	last_command(t_cmd **head, t_cmd **curr, char **args, int i)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->argv = args;
	new->next = NULL;
	args[i] = NULL;
	if (!*head)
		*head = new;
	else
		(*curr)->next = new;
	*curr = new;
}

/*Va créer une nouvelle liste appelé cmd pour parser les commandes
externes avec leurs arguments*/
t_cmd	*parse_commands(t_list *lst)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_list	*tmp;
	char	**args;
	int		i;

	head = NULL;
	curr = NULL;
	tmp = lst;
	args = malloc(sizeof(char *) * 100);
	i = 0;
	while (tmp)
	{
		i = new_commmand(&head, &curr, tmp, &args, i);
		if (i == -1)
			return (NULL);
		tmp = tmp->next;
	}
	last_command(&head, &curr, args, i);
	return (head);
}
