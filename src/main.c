/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/18 15:00:11 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line(); // remet une nouvelle ligne
	rl_replace_line("", 0); // clean l’input
	rl_redisplay(); // réaffiche le prompt
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
	lst = NULL;
	env = NULL;
	init_env(&env, envp);
	ft_init_commands(envbuilt, builtins);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		lst = NULL;
		input = readline("minishell: ");
		if (input && *input)
		{
			result = ft_splitou(input);
			ft_init_lst(&lst, result);
			ft_put_lst(lst);
			free_tokens(result);
			add_history(input);
			is_command(env, lst, builtins, envbuilt);
		}
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (!input)
		{
			printf("exit\n");
			break;
		}
		free (input);
		ft_lstclear(&lst, free);
	}
	return (0);
}
