/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:14:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/15 20:14:59 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Verifie le code de sortie s'il existe*/
int	check_exit_code(t_g *g)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	g->lst = g->lst->next;
	if (g->lst)
	{
		key = extract_check_key((char *)g->lst->content);
		if (!key)
			return (0);
		while (key[i])
		{
			if (!ft_isdigit(key[i]) && key[i] != '-')
				return (printf("Invalid exit option: '%s'\n", key), -20);
			i++;
		}
		if (g->lst->next)
			return (printf("Too much ARGS in exit option\n"), -20);
		i = ft_atoi(key);
		return (free(key), i);
	}
	return (0);
}

/*Clean tout ce qui peut être allouer en mémoire*/
void	free_n_exit(t_g *g)
{
	int	return_code;

	if (g->lst)
		return_code = check_exit_code(g);
	if (return_code == -20)
		return ;
	if (g->lst)
		ft_lstclear(&g->lst, free);
	if (g->env)
		free_env(&g->env);
	if (g->builtin)
		free(g->builtin);
	if (g->envbuilt)
		free(g->envbuilt);
	free(g);
	printf(RED "exit\n" RE);
	exit (return_code);
}
