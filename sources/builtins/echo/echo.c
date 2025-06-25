/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:25:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/25 14:07:54 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*Verifie si l'option "-n" est valide*/
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

/*Affiche l'argument*/
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

/*Affiche l'argument et traite s'il y a l'option "-n"*/
void	display_with_args(t_cmd *cmds)
{
	int		newline;
	int		i;

	i = 1;
	newline = 1;
	while (cmds->argv && ft_strnstr(cmds->argv[i], "-n", 2))
	{
		if (!is_valid_option(cmds->argv[i]))
			break ;
		i++;
		newline = 0;
	}
	while (cmds->argv && cmds->argv[i])
	{
		display_content(cmds->argv[i]);
		if (cmds->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		printf("\n");
}

// void	display_with_args(t_list *arg)
// {
// 	int		newline;

// 	newline = 1;
// 	while (arg && arg->content && ft_strnstr((char *)arg->content, "-n", 2))
// 	{
// 		if (!is_valid_option((char *)arg->content))
// 			break ;
// 		arg = arg->next;
// 		newline = 0;
// 	}
// 	while (arg && arg->content)
// 	{
// 		display_content((char *)arg->content);
// 		if (arg->next && arg->next->content)
// 			write(1, " ", 1);
// 		arg = arg->next;
// 	}
// 	if (newline)
// 		printf("\n");
// }

/*Appel la fonction echo*/
int	ft_echo(t_g *g, t_cmd *cmds)
{
	(void)g;
	if (cmds->argv[0] && cmds->argv[1])
		display_with_args(cmds);
	else
		printf("\n");
	return (0);

	// t_list	*arg;

	// arg = g->lst->next;
	// if (arg && arg->content)
	// 	display_with_args(arg);
	// else
	// 	printf("\n");
	// return (0);
}
