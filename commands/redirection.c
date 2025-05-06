/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/06 19:21:01 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_redirection(t_list *lst)
{
	t_list	*file;
	int		fd;
	int		newfd;

	file = NULL;
	while (lst)
	{
		if (ft_strcmp((char *)lst->content, ">") == 0)
		{
			file = lst->next;
			fd = open((char *)file->content, O_WRONLY);
			if (fd < 0)
			{
				perror("Error");
				return (0);
			}
			newfd = dup2(fd, STDOUT_FILENO);
		}
		lst = lst->next;
	}
	return (0);
}
