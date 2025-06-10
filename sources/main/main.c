/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/10 15:43:12 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void print_cmds(t_cmd *cmds)
{
	int i = 0;
	if (!cmds)
		return ;
	while (cmds)
	{
		printf("=== Command %d ===\n", i);
		for (int j = 0; cmds->argv && cmds->argv[j]; j++)
			printf("argv[%d]: %s\n", j, cmds->argv[j]);
		cmds = cmds->next;
		i++;
	}
}

void	sigint_handler(int sig)
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

int	msh_while(t_g *g)
{
	t_list *original;
	if (g->input && *g->input)
	{
		g->result = search_var(ft_splitou(g->input), g->env);
		if (!g->result)
			return (1);
		ft_init_lst(&g->lst, g->result);
		original = g->lst;
		if (is_redirection(g))
		{
			if (is_pipe(g))
			{
				g->lst = original;
				g->cmds = parse_commands(g->lst);
				print_cmds(g->cmds);
				if (!exec_pipeline(g, g->cmds, get_envp_array(g->env)))
					printf("%s: command not found\n", (char *)g->lst->content);
				free_cmds(g->cmds);
			}
			else if (!is_command(g))
			{
				printf("Is_command ne fonctionne pas\n");
				restore_std(g);
				g->lst = original;
				g->cmds = parse_commands(g->lst);
				// if (!exec_pipeline(g, g->cmds, get_envp_array(g->env)))
				// 	printf("%s: command not found\n", (char *)g->lst->content);
				free_cmds(g->cmds);
			}
			restore_std(g);
		}
	}
	return (0);
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
	if (!g->env)
		return (printf(RED "No ENV for the shell detected\nEXIT\n" RE), 1);
	while (1)
	{
		g->lst = NULL;
		g->input = readline(GREEN "minishell$ " RE);
		if (msh_while(g))
			return (1);
		if (!g->input)
			return (free_n_exit(g), 0);
		free_for_nextl(g->input, g->lst);
	}
	return (0);
}

//sigint_handler:
//remet une nouvelle ligne, clean l’input, réaffiche le prompt
