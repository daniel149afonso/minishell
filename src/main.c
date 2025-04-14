/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:19 by apiscopo          #+#    #+#             */
/*   Updated: 2025/04/14 19:34:34 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(void)
{
	char		*input;
	char		**result;
	t_list		*lst;
	t_builtin	builtins[8];

	lst = NULL;
	ft_init_commands(builtins);
	while (1)
	{
		lst = NULL;
		input = readline("minishell:");
		if (input && *input)
		{
			result = ft_splitou(input);
			ft_init_lst(&lst, result);
			ft_put_lst(lst);
			free_tokens(result, 0);
			add_history(input);
			is_command(lst, builtins);
		}
		free (input);
		ft_lstclear(&lst, NULL);
	}
	return (0);
}
