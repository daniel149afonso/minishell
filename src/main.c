/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/18 16:52:39 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header/minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	free_for_nextl(char *input, t_list *lst)
{
	free (input);
	ft_lstclear(&lst, free);
}

int	main(int ac, char **av, char **envp)
{
	t_g	*g;

	(void)ac;
	(void)**av;
	g = NULL;
	init(&g, envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g->lst = NULL;
		g->input = readline("minishell :");
		if (g->input && *g->input)
		{
			g->result = ft_splitou(g->input);
			ft_init_lst(&g->lst, g->result);
			is_command(g->env, g->lst, g->builtin, g->envbuilt);
		}
		if (!g->input)
			return (ft_lstclear(&g->lst, free), printf("exit\n"), 0);
		free_for_nextl(g->input, g->lst);
	}
	return (0);
}
//sigint_handler:
//remet une nouvelle ligne, clean l’input, réaffiche le prompt
