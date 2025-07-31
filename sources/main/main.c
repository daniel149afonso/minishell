/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:05:02 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/31 18:24:14 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	g_in_prompt;

static void	sigint_handler(int sig)
{
	if (g_in_prompt)
	{
		(void)sig;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		return ;
}

static void	free_for_nextl(char *input, t_g *g)
{
	if (input)
		free (input);
	if (g->prompt)
		free (g->prompt);
	if (g->lst)
		ft_lstclear(&g->lst, free);
}

static void	exec_parsing(t_g *g)
{
	if (collect_heredocs(g, g->cmds) != 0 || g->interrupted)
	{
		g->interrupted = 0;
		restore_std(g);
		free_cmds(g->cmds);
		g->cmds = NULL;
		return ;
	}
	else if (is_pipe(g->lst))
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
	restore_std(g);
}

static int	msh_while(t_g *g)
{
	add_history(g->input);
	if (g->input && *g->input)
	{
		if (g->env)
		{
			g->result = search_var(ft_splitou(g->input), g->env);
			if (!g->result)
				return (1);
			else if (is_space_command(g->result))
				return (free_split(g->result), 0);
			ft_init_lst(&g->lst, g->result);
			if (!validate_redirection_syntax(g->lst))
				return (0);
			remove_quotes(&g->lst);
			g->cmds = parse_commands(g->lst);
			if (g->debug_option)
				print_debug_command(g->cmds);
			exec_parsing(g);
			free_cmds(g->cmds);
			g->cmds = NULL;
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_g		*g;

	(void)ac;
	g = NULL;
	init_global_struct(&g, envp);
	is_debug_active(g, av[1]);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		g->lst = NULL;
		g_in_prompt = 1;
		g->prompt = ft_prompt();
		g->input = readline(g->prompt);
		g_in_prompt = 0;
		if (msh_while(g))
			return (1);
		if (!g->input)
			return (free_n_exit(g, g->cmds), 0);
		free_for_nextl(g->input, g);
	}
	return (0);
}
