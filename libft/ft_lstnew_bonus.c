/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:58:16 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/20 15:44:12 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

/*int	main(void)
{
	t_list	*list = ft_lstnew(ft_strdup("Hello"));
	printf("%s\n", (char *)list->content);
	free(list->content);
	free(list);
	return (0);
}*/
//BUT: ajouter du contenu a une liste et retourner la liste
//list->next = NULL marque la fin de la liste(similaire '\0')
