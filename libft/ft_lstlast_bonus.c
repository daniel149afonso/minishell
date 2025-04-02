/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:40:30 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/20 17:01:20 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

/*int	main(void)
{
	t_list	*lst;
	t_list	*lst1;
	t_list	*result;

	lst = malloc(sizeof(t_list));
	lst1 = malloc(sizeof(t_list));

	lst->content = "John Snow";
	lst1->content = "Arya Stark";

	lst->next = lst1;
	lst1->next = NULL;

	result = ft_lstlast(lst);
	printf("%s\n", (char *)result->content);
	return (0);
}*/
//BUT: Trouver le dernier element de la liste chaine
//instead of looping directly over the element, we check if
//there is a next element in the list, if not, that means we
//reached the end and we have to return the current pointer
//
