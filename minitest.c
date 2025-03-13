/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:19 by apiscopo          #+#    #+#             */
/*   Updated: 2025/03/13 21:04:51 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	char	**result;
	int		i;
	t_list	*lst;

	i = 0;
	lst = NULL;
	while (1)
	{
		input = readline("minishell:");
		if (*input)
		{
			result = ft_splitou(input);
			ft_init_lst(&lst, result);
			//ft_put_lst(lst); ICI!!!!!!!!!!!!!!!!!!!! decomente si tu veux tester mon choux (;
			add_history(input);
		}
		while (result[i] != NULL)
			printf("%s\n", result[i++]);
		free (result[i]);
		i = 0;
		free (input);
	}
	return (0);
}
