/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/25 18:02:51 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	free_for_nextl(char *input, t_list *lst)
{
	free (input);
	ft_lstclear(&lst, free);
}

static void	exec_parsing(t_g *g)
{
	if (!validate_redirection_syntax(g->lst))
		return ;
	remove_quotes(&g->lst);
	g->cmds = parse_commands(g->lst);
	print_debug_command(g->cmds);
	if (is_pipe(g->lst))
	{
		if (!exec_pipeline(g, g->cmds, get_envp_array(g->env)))
		{
			printf("%s: command not found\n", (char *)g->lst->content);
			return_code(g->env, 1);
		}
	}
	else if (!builtins(g, g->cmds))
	{
		if (!exec_pipeline(g, g->cmds, get_envp_array(g->env)))
		{
			printf("%s: command not found\n", (char *)g->lst->content);
			return_code(g->env, 1);
		}
	}
	free_cmds(g->cmds);
	restore_std(g);
}


int	msh_while(t_g *g)
{
	if (g->input && *g->input)
	{
		g->result = search_var(ft_splitou(g->input), g->env);
		if (!g->result)
			return (1);
		ft_init_lst(&g->lst, g->result);
		exec_parsing(g);
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
		add_history(g->input);
		if (msh_while(g))
			return (1);
		if (!g->input)
			return (free_n_exit(g, g->cmds), 0);
		free_for_nextl(g->input, g->lst);
	}
	return (0);
}
