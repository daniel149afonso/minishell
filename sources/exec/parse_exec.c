/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:48:48 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/04 22:14:25 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int new_commmand(t_cmd **head, t_cmd **curr, t_list *tmp, char ***args, int i)
{
	if (ft_strcmp(tmp->content, "|") == 0)
	{
		(*args)[i] = NULL;

		t_cmd *new = malloc(sizeof(t_cmd));
		if (!new)
			return -1;
		new->argv = *args;
		new->next = NULL;

		if (!*head)
			*head = new;
		else
			(*curr)->next = new;
		*curr = new;

		*args = malloc(sizeof(char *) * 100);
		return 0; // reset index i
	}
	else
	{
		(*args)[i++] = ft_strdup(tmp->content);
	}
	return i;
}


void last_command(t_cmd **head, t_cmd **curr, char **args, int i)
{
	args[i] = NULL;

	t_cmd *new = malloc(sizeof(t_cmd));
	new->argv = args;
	new->next = NULL;

	if (!*head)
		*head = new;
	else
		(*curr)->next = new;
	*curr = new;
}

t_cmd *parse_commands(t_list *lst)
{
	t_cmd *head = NULL;
	t_cmd *curr = NULL;
	t_list *tmp = lst;
	char **args = malloc(sizeof(char *) * 100); //a changer
	int i;

    i = 0;
	while (tmp)
	{
        i = new_commmand(&head, &curr, tmp, &args, i);
        if (i == -1)
			return NULL;
	    tmp = tmp->next;
	}
    last_command(&head, &curr, args, i);
	return head;
}
