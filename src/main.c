/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/18 15:30:27 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header/minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line(); // remet une nouvelle ligne
	rl_replace_line("", 0); // clean l’input
	rl_redisplay(); // réaffiche le prompt
}

static void	free_for_nextl(char *input, t_list *lst)
{
	free (input);
	ft_lstclear(&lst, free);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	char		**result;
	t_list		*lst;
	t_env		*env;
	t_builtin	builtins[8];
	t_envbuilt	envbuilt[3];

	(void)ac;
	(void)**av;
	env = NULL;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	init(&env, envp, envbuilt, builtins);
	while (1)
	{
		lst = NULL;
		input = readline("minishell :");
		if (input && *input)
		{
			result = ft_splitou(input);
			ft_init_lst(&lst, result);
			is_command(env, lst, builtins, envbuilt);
		}
		if (!input)
			return (ft_lstclear(&lst, free), printf("exit\n"), 0);
		free_for_nextl(input, lst);
	}
	return (0);
}
