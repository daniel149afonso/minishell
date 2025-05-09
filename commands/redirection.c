/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/08 15:27:19 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_redirection(t_list *lst)
{
	t_list	*file;
	int		fd;

	file = NULL;
	while (lst)
	{
		if (ft_strcmp((char *)lst->content, ">") == 0)
		{
			file = lst->next;
			fd = open((char *)file->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open failed");
				return (0);
			}
			printf("Je suis entré\n");
			dup2(fd, STDOUT_FILENO);
			close(fd);
			printf("hello\n");
		}
		lst = lst->next;
	}
	return (0);
}
