/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:19 by apiscopo          #+#    #+#             */
/*   Updated: 2025/04/16 20:46:17 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
		free (input);
		ft_lstclear(&lst, free);
	}
	return (0);
}
