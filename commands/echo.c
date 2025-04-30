/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:25:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/30 20:32:18 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// void	search_variable(char *path)
// {
// 	char	*equal_sign;
// 	int		len;

// 	len = ft_strlen(path);
// 	equal_sign = ft_strchr(path, '=');
// 	while (condition)
// 	{
// 		/* code */
// 	}

// }

void	display_inside_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			// On saute le caractère de quote
			i++;
			continue ;
		}
		write(1, &str[i], 1);
		i++;
	}
}


void	display_with_args(t_list *arg)
{
	int		newline;

	newline = 1;
	while (arg && arg->content && ft_strcmp((char *)arg->content, "-n") == 0)
	{
		arg = arg->next;
		newline = 0;
	}
	while (arg && arg->content)
	{
		display_inside_quotes((char *)arg->content);
		arg = arg->next;
		if (arg && arg->content)
			printf(" ");
	}
	if (newline)
		printf("\n");
}

void	ft_echo(t_g *g)
{
	t_list	*arg;

	arg = g->lst->next;
	if (arg && arg->content)
	{
		display_with_args(arg);
	}
	else
		printf("\n");
	return ;
}
