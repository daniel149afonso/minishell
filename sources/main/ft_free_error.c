/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:19:37 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/04 22:13:27 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_error(char *msg, t_list **lst)
{
	ft_free_lst(lst);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_free_lst(t_list **lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	tokens = NULL;
}

void	print_path_error(char *path)
{
	write(2, "minishell: cd: ", 16);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory", 28);
	write(2, "\n", 1);
}
