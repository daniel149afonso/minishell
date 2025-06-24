/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:48:48 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/24 18:39:24 by daniel149af      ###   ########.fr       */
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

int	handle_redirection_token(t_list **tmp, t_cmd **curr)
{
	t_list *redir = *tmp;

	if (!redir || !redir->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return 1;
	}

	if (!ft_strcmp(redir->content, "<"))
		store_stdin_redir(*curr, redir);
	else if (!ft_strcmp(redir->content, ">"))
		store_stdout_redir(*curr, redir);
	else if (!ft_strcmp(redir->content, ">>"))
		store_append_redir(*curr, redir);
	// On peut ajouter ici << plus tard

	// Avancer tmp de 2 tokens (redir + fichier)
	*tmp = redir->next->next;
	return 0;
}

t_cmd *parse_commands(t_list *lst)
{
    t_cmd  *head = NULL, *curr = NULL;
    char   **args = NULL;
    int     i = 0;
    t_list *tmp = lst;

    while (tmp)
    {
        // 1) REDIRECTION
        if (is_redirection_token(tmp->content))
        {
            // erreur si pas de commande ET pas d'args
            if (!curr && (!args || i == 0))
            {
                printf("minishell: syntax error near unexpected token `newline'\n");
                return NULL;
            }
            // si on a des args accumulés, on crée la commande avant la redirection
            if (!curr && args && i > 0)
            {
                args[i] = NULL;
                curr = create_new_cmd(args);
                if (!curr) return NULL;
                head = curr;
                // ► on réalloue args pour la suite, i redevient 0
                args = malloc(sizeof(char *) * 100);
                if (!args) return NULL;
                i = 0;
            }

            // on attache la redirection à curr
            handle_redirection_token(&tmp, &curr);
            continue;
        }

        // 2) PIPE
        if (ft_strcmp(tmp->content, "|") == 0)
        {
            // autoriser uniquement si une commande existe à gauche
            if (i == 0 && curr == NULL)
            {
                printf("minishell: syntax error near unexpected token `|'\n");
                return NULL;
            }
            // terminer argv[]
            args[i] = NULL;
            // créer le nouveau t_cmd
            t_cmd *new = create_new_cmd(args);
            if (!new) return NULL;
            if (!head) head = new;
            else        curr->next = new;
            curr = new;
            // préparer le buffer d'args pour la prochaine commande
            args = malloc(sizeof(char *) * 100);
            if (!args) return NULL;
            i = 0;
            tmp = tmp->next;
            continue;
        }

        // 3) ARGUMENT NORMAL
        if (!args)
        {
            args = malloc(sizeof(char *) * 100);
            if (!args) return NULL;
            i = 0;
        }
        args[i++] = ft_strdup(tmp->content);
        tmp = tmp->next;
    }

    // 4) DERNIÈRE COMMANDE
    if ((args && i > 0) || (curr && (curr->infile || curr->outfile)))
    {
        if (args)
        {
            args[i] = NULL;
            t_cmd *new = create_new_cmd(args);
            if (!new) return NULL;
            if (!head) head = new;
            else        curr->next = new;
            curr = new;
        }
    }
    else
        free(args);

    return head;
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
