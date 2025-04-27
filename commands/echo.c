/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:25:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/27 20:17:29 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	display_content(t_list *arg)
{
	while (arg && arg->content)
	{
		printf("%s", (char *)arg->content);
		if (arg->next && arg->next->content)
			printf(" ");
		arg = arg->next;
	}
}

void	display_inside_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				printf("%c", str[i]);
				i++;
			}
			if (str[i])
				i++; // passer la fermeture de quote
		}
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
}

void	display_with_args_v2(t_list *arg)
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
		display_with_args_v2(arg);
	}
	else
		printf("\n");
	return ;
}
