/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:19:42 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/20 16:39:54 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/*int	main(void)
{
	t_list	*lst;
	t_list	*lst2;

	lst = malloc(sizeof(lst));
	lst2 = malloc(sizeof(lst));
	lst->next = lst2;
	printf("%d\n", ft_lstsize(lst));
	return (0);
}*/
//BUT: Compter le nombre d'element d'une liste chainee
//On initialise tmp avec lst evite decraser valeur de lst
//(le pointeur vers le début de la liste)
//while (tmp)// Tant que tmp n'est pas NULL (tant qu'il y a un élément)
//tmp = tmp->next; // On avance dans la liste (pointe vers le prochain elem)
