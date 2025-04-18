/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:01:11 by daafonso          #+#    #+#             */
/*   Updated: 2025/04/17 23:24:37 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	free_tokens(tokens, 0);
	ft_put_lst(*(lst));
}

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
//FT_INIT_LST:
//crée un nouvel element de type t_list pour chaque token
//puis assemble chaque elem pour former une liste chainée
//-------------------------------------------------------------
//FT_PUT_LST
//Affiche le contenu de chaque element de la liste