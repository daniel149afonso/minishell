/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:54:57 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/21 12:45:06 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}
/*
void	del_content(void *content)
{
	free(content);
}
*/
//BUT: supprime tous les elements d'une liste ainsi que leur contenu
//en liberant la memoire
//tmp = (*lst)->next Cree une sauvegarde de l'element suivant
//pour ne pas perdre son acces
//ft_lstdelone(*lst, del); //Supprime l'élément courant en utilisant del
//*lst = tmp;              // Passe à l'élément suivant
