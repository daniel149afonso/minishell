/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/26 18:03:31 by apiscopo         ###   ########.fr       */
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
	int 	return_code;
	int		i;
	char	*key;

	return_code = 0;
	i = 0;
	key = NULL;
	if ((g->lst = g->lst->next))
	{
		key = extract_check_key((char *)g->lst->content);
		if (!key)
			return 0;
		while (key[i])
		{
			if (!ft_isdigit(key[i]) && key[i] != '-')
				return (printf("Invalid exit option: '%s'\n", key), -20);
			i++;
		}
		if (g->lst->next)
			return (printf("Too much ARGS in exit option\n"), -20);
		return_code = ft_atoi(key);
		return (free(key), return_code);
	}
	return (0);
}

void	free_n_exit(t_g *g)
{
	int return_code;

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
	if (!g->env)
		return (free_n_exit(g), 0);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g->lst = NULL;
		g->input = readline(GREEN "minishell $" RE);
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
