/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:14:05 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/21 22:16:13 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_missing_arg(t_list *lst)
{
	if ((ft_strcmp((char *)lst->content, ">") == 0 && !lst->next) \
	|| (ft_strcmp((char *)lst->content, ">>") == 0 && !lst->next) \
	|| (ft_strcmp((char *)lst->content, "<") == 0 && !lst->next) \
	|| (ft_strcmp((char *)lst->content, "<<") == 0 && !lst->next))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (ft_strcmp((char *)lst->content, "<>") == 0)
	{
		printf("minishell: syntax error near unexpected token `<>'\n");
		return (1);
	}
	return (0);
}

char	*right_redir(t_list *lst)
{
	int	right;

	right = ft_strcmp((char *)lst->content, ">");
	if (!right && !ft_strcmp((char *)lst->next->content, "<"))
		return ("<");
	if (!right && !ft_strcmp((char *)lst->next->content, "<<"))
		return ("<<");
	if (!right && !ft_strcmp((char *)lst->next->content, ">>"))
		return (">>");
	right = ft_strcmp((char *)lst->content, ">>");
	if (!right && !ft_strcmp((char *)lst->next->content, "<"))
		return ("<");
	if (!right && !ft_strcmp((char *)lst->next->content, "<<"))
		return ("<<");
	if (!right && !ft_strcmp((char *)lst->next->content, ">"))
		return (">");
	if (!right && !ft_strcmp((char *)lst->next->content, ">>"))
		return (">>");
	return (NULL);
}

char	*left_redir(t_list *lst)
{
	int	left;

	left = ft_strcmp((char *)lst->content, "<");
	if (!left && !ft_strcmp((char *)lst->next->content, ">"))
		return (">");
	if (!left && !ft_strcmp((char *)lst->next->content, "<<"))
		return ("<<");
	if (!left && !ft_strcmp((char *)lst->next->content, ">>"))
		return (">>");
	left = ft_strcmp((char *)lst->content, "<<");
	if (!left && !ft_strcmp((char *)lst->next->content, "<"))
		return ("<");
	if (!left && !ft_strcmp((char *)lst->next->content, "<<"))
		return ("<<");
	if (!left && !ft_strcmp((char *)lst->next->content, ">"))
		return (">");
	if (!left && !ft_strcmp((char *)lst->next->content, ">>"))
		return (">>");
	return (NULL);
}

int	is_mixed_redir(t_list *lst)
{
	char	*right;
	char	*left;

	right = right_redir(lst);
	left = left_redir(lst);
	if (right || left)
	{
		if (right)
			printf("minishell: syntax error near unexpected token `%s'\n", \
				right);
		else
			printf("minishell: syntax error near unexpected token `%s'\n", \
				left);
		return (1);
	}
	return (0);
}

int	parsing_redir(t_list *lst)
{
	while (lst)
	{
		if (is_missing_arg(lst))
			return (1);
		if (is_mixed_redir(lst))
			return (1);
		lst = lst->next;
	}
	return (0);
}