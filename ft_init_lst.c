/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:01:11 by daafonso          #+#    #+#             */
/*   Updated: 2025/03/13 21:05:27 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_lst(t_list **lst, char **tokens)
{
	int		j;

	j = 0;
	while (tokens[j])
	{
		if (j == 0)
			*lst = ft_lstnew((char *)tokens[j]);
		else
			ft_lstadd_back(lst, ft_lstnew((char *)tokens[j]));
		j++;
	}
}

void	ft_put_lst(t_list *lst)
{
	t_list	*tmp;

	while (tmp)
	{
		tmp = lst->next;
		printf("Content: %s\n", (char *)lst->content);
		lst = tmp;
	}
}
//FT_INIT_LST:
//crée un nouvel element de type t_list pour chaque token
//puis assemble chaque elem pour former une liste chainée
//-------------------------------------------------------------
//FT_PUT_LST
//Affiche le contenu de chaque element de la liste