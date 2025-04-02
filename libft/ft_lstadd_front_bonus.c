/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:45:05 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/20 16:12:10 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
//BUT: ajouter un nouvel elem de type t_list au debut
//l'ancien premier elem devient le suivant
//new->next = *lst; lst devient l'element suivant
//*lst = new; new devient le premier element
