/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:25:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/14 14:54:53 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_valid_option(char *option)
{
	int	i;

	i = 0;
	i++;
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	display_content(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	display_with_args(t_list *arg)
{
	int		newline;

	newline = 1;
	while (arg && arg->content && ft_strnstr((char *)arg->content, "-n", 2))
	{
		if (!is_valid_option((char *)arg->content))
			break ;
		arg = arg->next;
		newline = 0;
	}
	while (arg && arg->content)
	{
		display_content((char *)arg->content);
		if (arg->next && arg->next->content)
		write(1, " ", 1);
		arg = arg->next;
	}
	if (newline)
		printf("\n");
}

void	ft_echo(t_g *g)
{
	t_list	*arg;

	arg = g->lst->next;
	if (arg && arg->content)
		display_with_args(arg);
	else
		printf("\n");
	return ;
}
