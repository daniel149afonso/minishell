/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:14:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/05 01:11:28 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* Vérifie qu’on a bien un entier, avec un +/- optionnel en première position */
int	is_valid_numeric_arg(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_exit_code(t_g *g)
{
	char	*key;
	int		code;

	g->lst = g->lst->next;
	code = 0;
	if (g->lst)
	{
		key = extract_check_key((char *)g->lst->content);
		if (!key)
			return (0);
		if (!is_valid_numeric_arg(key))
		{
			return_code(g->env, 2);
			ft_putstr_fd("exit: ", 2);
			return (ft_putstr_fd("numeric argument required\n", 2), 255);
		}
		if (g->lst->next)
			return (return_code(g->env, 2), ft_putstr_fd("minishell: exit: "
					"too many arguments\n", 2), -20);
		code = ft_atoi(key);
		free(key);
		return (code);
	}
	return (0);
}

/*Clean tout ce qui peut être allouer en mémoire*/
int	free_n_exit(t_g *g, t_cmd *cmds)
{
	int	return_code;

	(void)cmds;
	if (g->lst)
		return_code = check_exit_code(g);
	else
		return_code = 0;
	if (return_code == -20)
		return (1);
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
