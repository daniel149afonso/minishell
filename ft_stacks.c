/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:01:11 by daafonso          #+#    #+#             */
/*   Updated: 2025/03/12 17:08:45 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_stack(char **strs, t_list *lst)
{
	int	j;

	j = 0;
	while (strs[j])
	{
		lst->content = strs[j];
		if (!lst->content)
			ft_error()
	}

}
