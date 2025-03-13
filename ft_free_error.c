/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:09:06 by daafonso          #+#    #+#             */
/*   Updated: 2025/03/13 21:27:03 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *msg, t_list **lst)
{
	ft_free_lst(lst);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
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
