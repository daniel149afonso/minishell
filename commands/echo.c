/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:25:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/21 22:01:18 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	display_with_args(t_list *arg)
{
	t_list	*tmp;
	int		option;
	int		newline;

	option = 0;
	newline = 1;
	if (ft_strcmp((char *)arg->content, "-n") == 0)
	{
		option = 1;
		newline = 0;
	}
	while (arg && arg->content)
	{
		tmp = arg->next;
		if (ft_strcmp((char *)arg->content, "-n") != 0)
			printf("%s", (char *)arg->content);
		option = 0;
		arg = tmp;
	}
	(void)option;
	if (newline == 1)
		printf("\n");
}

void	ft_echo(t_list *lst)
{
	t_list	*arg;

	arg = lst->next;
	if (arg && arg->content)
	{
		display_with_args(arg);
	}
	else
		printf("\n");
	return ;
}