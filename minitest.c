/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:19 by apiscopo          #+#    #+#             */
/*   Updated: 2025/03/12 21:28:09 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*input;
	char	**result;
	int		i = 0;

	while (1)
	{
		input = readline("minishell:");
		if (*input)
		{
			result = ft_splitou(input);
			add_history(input);
		}
		while (result[i] != NULL)
		{
			printf("%s\n", result[i]);
			i++;
		}
		i = 0;
		free (input);
	}
	return 0;
}
