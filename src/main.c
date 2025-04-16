/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:19 by apiscopo          #+#    #+#             */
/*   Updated: 2025/04/16 17:28:52 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)**av;
	char		*input;
	char		**result;
	t_list		*lst;
	t_env		*env = NULL;
	t_builtin	builtins[8];

	lst = NULL;
	init_env(&env, envp);
	ft_init_commands(builtins);
	while (1)
	{
		lst = NULL;
		input = readline("minishell 🤖 : ");
		if (input && *input)
		{
			result = ft_splitou(input);
			ft_init_lst(&lst, result);
			ft_put_lst(lst);
			free_tokens(result, 0);
			add_history(input);
			is_command(env, lst, builtins);
		}
		free (input);
		ft_lstclear(&lst, NULL);
	}
	return (0);
}
