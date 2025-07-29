/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:14:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/28 18:27:08 by apiscopo         ###   ########.fr       */
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
	t_list	*tmp;

	tmp = g->lst->next;
	code = 0;
	if (tmp)
	{
		key = extract_check_key((char *)tmp->content);
		if (!key)
			return (0);
		if (!is_valid_numeric_arg(key))
		{
			return_code(g->env, 2);
			return (free(key),
				ft_putstr_fd("exit: numeric argument required\n", 2), 2);
		}
		if (tmp->next)
			return (return_code(g->env, 2), ft_putstr_fd("exit: "
					"too many arguments\n", 2), free(key), -20);
		code = ft_atoi(key);
		return (free(key), code);
	}
	return (0);
}

/*Clean tout ce qui peut être allouer en mémoire*/
int	free_n_exit(t_g *g, t_cmd *cmds)
{
	int	return_code;

	if (g->lst)
		return_code = check_exit_code(g);
	else
		return_code = 0;
	if (return_code == -20)
		return (1);
	if (g->lst)
		ft_lstclear(&g->lst, free);
	if (g->env)
		free_env(g->env);
	if (g->builtin)
		free(g->builtin);
	if (g->envbuilt)
		free(g->envbuilt);
	if (cmds)
		free_cmds(cmds);
	if (g->cmd)
		free(g->cmd);
	if (g->input)
		free(g->input);
	free(g);
	printf(RED "exit\n" RE);
	exit (return_code);
}
