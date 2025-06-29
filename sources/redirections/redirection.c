/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/29 15:16:49 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_redirection_token(char *token)
{
	return (!ft_strcmp(token, "<") || !ft_strcmp(token, ">") ||
			!ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"));
}

int	validate_redirection_syntax(t_list *lst)
{
	if (parsing_redir(lst))
		return (0);
	return (1);
}

