/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:48:48 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/26 19:13:32 by daniel149af      ###   ########.fr       */
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

// t_cmd *create_new_cmd(char **args)
// {
//     t_cmd *new = malloc(sizeof(t_cmd));
//     if (!new)
//         return NULL;
//     fprintf(stderr, "DEBUG: création commande avec argv[0] = '%s'\n",
//             args && args[0] ? args[0] : "NULL");
//     new->argv = args;
//     new->infile = NULL;
//     new->outfile = NULL;
//     new->append = 0;
//     new->next = NULL;
//     return new;
// }




// int handle_redir_safely(t_list **lst, t_cmd **head, t_cmd **curr,
//                         char ***args, int *i)
// {
//     if (*args && *i > 0)
//     {
//         (*args)[*i] = NULL;
//         t_cmd *new = create_new_cmd(*args);
//         if (!new)
//             return 0;
//         if (!*head)
//             *head = new;
//         else
//             (*curr)->next = new;
//         *curr = new;
//         *args = NULL;
//         *i = 0;
//     }
//     else if (!*curr)
//     {
//         printf("minishell: syntax error near unexpected token `newline'\n");
//         return 0;
//     }
//     return !handle_redirection_token(lst, curr);
// }

// int handle_pipe_if_needed(t_list **lst, t_cmd **head, t_cmd **curr,
//                           char ***args, int *i)
// {
//     if (ft_strcmp((*lst)->content, "|") != 0)
//         return 1;

//     if (*args && *i > 0)
//     {
//         (*args)[*i] = NULL;
//         t_cmd *new = create_new_cmd(*args);
//         if (!new) return 0;
//         if (!*head) *head = new;
//         else (*curr)->next = new;
//         *curr = new;
//         *args = NULL;
//         *i = 0;
//     }
//     else if (!*curr)
//     {
//         printf("minishell: syntax error near unexpected token `|'\n");
//         return 0;
//     }

//     // ❌ NE PAS faire : *lst = (*lst)->next;
//     return 1;
// }


// int finalize_last_command(t_cmd **head, t_cmd **curr, char ***args, int i)
// {
//     if ((*args && i > 0) || (*curr && ((*curr)->infile || (*curr)->outfile)))
//     {
//         if (*args && i > 0)
//         {
//             (*args)[i] = NULL;
//             t_cmd *new = create_new_cmd(*args);
//             if (!new)
//                 return 0;
//             if (!*head)
//                 *head = new;
//             else
//                 (*curr)->next = new;
//         }
//         else
//             free(*args);
//     }
//     else
//         free(*args);
//     return 1;
// }

// t_cmd *parse_commands(t_list *lst)
// {
//     t_cmd *head = NULL;
//     t_cmd *curr = NULL;
//     char **args = NULL;
//     int i = 0;

//     while (lst)
//     {
//         if (is_redirection_token(lst->content))
//         {
//             if (!handle_redir_safely(&lst, &head, &curr, &args, &i))
//                 return NULL;
//             continue;
//         }

//         if (ft_strcmp(lst->content, "|") == 0)
//         {
//             // PIPE trouvé
//             if (args && i > 0)
//             {
//                 args[i] = NULL;
//                 t_cmd *new = create_new_cmd(args);
//                 if (!new) return NULL;
//                 if (!head) head = new;
//                 else curr->next = new;
//                 curr = new;
//                 args = NULL;
//                 i = 0;
//             }
//             else if (!curr)
//             {
//                 printf("minishell: syntax error near unexpected token `|'\n");
//                 return NULL;
//             }

//             lst = lst->next;
//             continue;
//         }

//         if (!args && !(args = malloc(sizeof(char *) * 100)))
//             return NULL;

//         args[i++] = ft_strdup(lst->content);
//         lst = lst->next;
//     }

//     // Finaliser la dernière commande si nécessaire
//     if ((args && i > 0) || (curr && (curr->infile || curr->outfile)))
//     {
//         if (args && i > 0)
//         {
//             args[i] = NULL;
//             t_cmd *new = create_new_cmd(args);
//             if (!new) return NULL;
//             if (!head) head = new;
//             else curr->next = new;
//         }
//         else
//             free(args);
//     }
//     else
//         free(args);

//     return head;
// }


void free_cmd_list(t_cmd *cmds)
{
    t_cmd *tmp;
    int i = 0;

    while (cmds)
    {
        tmp = cmds->next;
        if (cmds->argv)
        {
            while (cmds->argv[i])
                free(cmds->argv[i++]);
            free(cmds->argv);
        }
        // Libère les redirs si nécessaire (si t_list allouée dynamiquement)
        // free_t_list(cmds->infile);
        // free_t_list(cmds->outfile);

        free(cmds);
        cmds = tmp;
        i = 0;
    }
}

int	handle_redirection_token(t_list **tmp, t_cmd **curr)
{
	t_list	*redir;

	redir = *tmp;
	if (!redir || !redir->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (!ft_strcmp(redir->content, "<"))
		store_stdin_redir(*curr, redir);
	else if (!ft_strcmp(redir->content, ">"))
		store_stdout_redir(*curr, redir);
	else if (!ft_strcmp(redir->content, ">>"))
		store_append_redir(*curr, redir);
	// On peut ajouter ici << plus tard
	*tmp = redir->next->next;
	return (0);
}

t_cmd *parse_single_command(t_list **lst)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;

    cmd->argv = malloc(sizeof(char *) * 100);
    if (!cmd->argv)
        return free(cmd), NULL;

    int i = 0;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->next = NULL;

    while (*lst && ft_strcmp((*lst)->content, "|") != 0)
    {
        if (is_redirection_token((*lst)->content))
        {
            if (handle_redirection_token(lst, &cmd))
                return free_cmds(cmd), NULL;
            continue;
        }
        cmd->argv[i++] = ft_strdup((*lst)->content);
        *lst = (*lst)->next;
    }
    cmd->argv[i] = NULL;
    return cmd;
}

t_cmd *parse_commands(t_list *lst)
{
    t_cmd *head = NULL;
    t_cmd *curr = NULL;

    while (lst)
    {
        t_cmd *cmd = parse_single_command(&lst);
        if (!cmd)
            return free_cmd_list(head), NULL;

        if (!head)
            head = cmd;
        else
            curr->next = cmd;
        curr = cmd;

        if (lst && ft_strcmp(lst->content, "|") == 0)
            lst = lst->next; // sauter le pipe
    }
    return head;
}




