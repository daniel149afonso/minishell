/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:34:07 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/21 12:49:21 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*void	del_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	lst->content = ft_strdup("John Snow");
	lst->next = NULL;

	ft_lstdelone(lst, del_content);
	printf("%s\n", (char *)lst->content);//Ne check pas is element empty Warning
	return (0);
}*/
//BUT: Supprimme l'element et son contenu en liberant la memoire alloue
//à cet élément ainsi qu'à son contenu
//en appelant une fonction de destruction (del) sur ce contenu.
