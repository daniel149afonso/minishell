/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/14 15:45:09 by daniel149af      ###   ########.fr       */
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

void	free_n_exit(t_g *g)
{
	if (g->lst)
		ft_lstclear(&g->lst, free);
	if (g->env)
		free_env(&g->env);
	if (g->builtin)
		free(g->builtin);
	if (g->envbuilt)
		free(g->envbuilt);
	free(g);
	printf("exit\n");
	exit (0);
}

int	main(int ac, char **av, char **envp)
{
	t_g	*g;

	(void)ac;
	(void)**av;
	g = NULL;
	init_global_struct(&g, envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g->lst = NULL;
		g->input = readline("minishell :");
		if (g->input && *g->input)
		{
			g->result = search_var(ft_splitou(g->input), g->env);
			if (!g->result)
				return (1);
			ft_init_lst(&g->lst, g->result);
			is_redirection(g);
			remove_redir_token(&g->lst);
			ft_put_lst(g->lst);
			if (!is_command(g))
			{
				if (g->lst && g->lst->content)
					printf("%s: command not found\n", (char *)g->lst->content);
			}
			if (g->s_stdout != -1)
			{
				// 🔁 restaurer stdout
				printf("%d stdout restauré\n", g->s_stdout);
				dup2(g->s_stdout, STDOUT_FILENO);
				close(g->s_stdout);
			}
		}
		if (!g->input)
			return (free_n_exit(g), 0);
		free_for_nextl(g->input, g->lst);
	}
	return (0);
}

//sigint_handler:
//remet une nouvelle ligne, clean l’input, réaffiche le prompt
