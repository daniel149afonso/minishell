/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:25:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/03 23:25:38 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../header/minishell.h"

void	handle_single_double(char *str, int first_quote)
{
	int	i;

	i = 0;
	if (first_quote == '\'')
	{
		while (str[i])
		{
			if (str[i] != '\'')
				write(1, &str[i], 1);
			i++;
		}
	}
	else
	{
		while (str[i])
		{
			if (str[i] != '"')
				write(1, &str[i], 1);
			i++;
		}
	}
}

void	find_first_quote(char *str)
{
	int	i;
	int	first_quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			first_quote = str[i];
			handle_single_double(str, first_quote);
			break ;
		}
		
	}
	
}

void	display_inside_quotes(char *str)
{
	int		i;

	i = 0;
	printf("DEBUG: [%s]\n", str);
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
	while (arg && arg->content && ft_strcmp((char *)arg->content, "-n") == 0)
	{
		arg = arg->next;
		newline = 0;
	}
	while (arg && arg->content)
	{
		display_inside_quotes((char *)arg->content);
		if (arg->next && arg->next->content)
			printf(" ");
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
	{
		display_with_args(arg);
	}
	else
		printf("\n");
	return ;
}
