/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:09:06 by daafonso          #+#    #+#             */
/*   Updated: 2025/04/16 20:21:55 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void	free_tokens(char **tokens, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(tokens[i++]);
	free(tokens);
}

void	print_cd_error(char *path)
{
	write(2, "cd: no such file or directory: ", 32);
	write(2, path, strlen(path));
	write(2, "\n", 1);
}
