/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/27 16:41:06 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

int	check_exit_code(t_g *g)
{
	int		return_code;
	int		i;
	char	*key;

	return_code = 0;
	i = 0;
	key = NULL;
	if ((g->lst = g->lst->next))
	{
		key = extract_check_key((char *)g->lst->content);
		if (!key)
			return (0);
		while (key[i])
		{
			if (ft_isalpha(key[i]))
				return (printf("Invalid exit option: %s\n", key), -1);
			i++;
		}
		if (g->lst->next)
			return (printf("Too much ARGS in exit option\n"), -1);
		return_code = ft_atoi(key);
		return (return_code);
	}
	return (0);
}

void	free_n_exit(t_g *g)
{
	int	return_code;

	return_code = check_exit_code(g);
	if (return_code < 0)
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
	printf("exit\n");
	exit (return_code);
}

int	msh_while(t_g *g)
{
	if (g->input && *g->input)
	{
		g->result = search_var(ft_splitou(g->input), g->env);
		if (!g->result)
			return (1);
		ft_init_lst(&g->lst, g->result);
		if (is_redirection(g))
		{
			remove_redir_token(&g->lst);
			remove_quotes(&g->lst);
			if (!is_command(g))
			{
				restore_std(g);
				if (g->lst && g->lst->content)
					printf("%s: command not found\n", (char *)g->lst->content);
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
	while (1)
	{
		g->lst = NULL;
		g->input = readline("minishell$ ");
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
