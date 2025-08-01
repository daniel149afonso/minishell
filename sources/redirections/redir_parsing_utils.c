/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/08/01 15:31:21 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Check si c'est une redirection*/
int	is_redirection_token(char *token)
{
	return (!ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"));
}

/*Check s'il y a un argument après la redirection,
si non return une erreur*/
int	is_missing_arg(t_list *lst)
{
	if ((ft_strcmp((char *)lst->content, ">") == 0 && !lst->next)
		|| (ft_strcmp((char *)lst->content, ">>") == 0 && !lst->next)
		|| (ft_strcmp((char *)lst->content, "<") == 0 && !lst->next)
		|| (ft_strcmp((char *)lst->content, "<<") == 0 && !lst->next))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (ft_strcmp((char *)lst->content, "<>") == 0)
	{
		printf("minishell: syntax error near unexpected token `<>'\n");
		return (1);
	}
	return (0);
}

t_g	*get_heredoc_context(t_g *new_context)
{
	static t_g	*context = NULL;

	if (new_context)
		context = new_context;
	return (context);
}

void	heredoc_sigint_handler(int sig)
{
	t_g	*g;

	(void)sig;
	write(1, "\n", 1);
	g = get_heredoc_context(NULL);
	if (g)
		free_n_exit_child(g, NULL, 130);
}
