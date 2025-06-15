/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:01:11 by daafonso          #+#    #+#             */
/*   Updated: 2025/06/15 17:30:13 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*crée un nouvel element de type t_list pour chaque token
puis assemble chaque element pour former une liste chainée*/
void	ft_init_lst(t_list **lst, char **tokens)
{
	int		j;

	j = 0;
	while (tokens[j])
	{
		if (j == 0)
			*lst = ft_lstnew(ft_strdup(tokens[j]));
		else
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(tokens[j])));
		j++;
	}
	free_tokens(tokens);
	ft_put_lst(*lst);
}

/*Affiche le contenu de chaque element de la liste*/
void	ft_put_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		printf("DEBUG | Content: %s\n", (char *)lst->content);
		lst = tmp;
	}
}
