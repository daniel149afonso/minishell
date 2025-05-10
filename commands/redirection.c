/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/09 20:45:33 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_redirection(t_list *lst)
{
	t_list	*file;
	int		fd;
	int		original_stdout;
	int		res;
	
	res = 0;
	file = NULL;
	while (lst)
	{
		if (ft_strcmp((char *)lst->content, ">") == 0)
		{
			res = 1;
			file = lst->next;
			fd = open((char *)file->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open failed");
				return (0);
			}
			// 💾 sauvegarder stdout
			original_stdout = dup(STDOUT_FILENO);

			// 🔁 rediriger stdout vers le fichier
			dup2(fd, STDOUT_FILENO);
			close(fd);

			// 🔁 restaurer stdout
			// dup2(original_stdout, STDOUT_FILENO);
			close(original_stdout);
		}
		lst = lst->next;
	}
	return (res);
}
