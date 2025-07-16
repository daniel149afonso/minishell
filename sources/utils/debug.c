/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:11:55 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/16 18:14:59 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Check si le debug mode est actif*/
void	is_debug_active(t_g *g, char *debug)
{
	if (debug)
	{
		if ((strncmp(debug, "debug", ft_strlen(debug))) == 0)
		{
			printf(RED"\n---DEBUG MODE IS NOW ACTIVE---\n\n"RE);
			g->debug_option = 1;
		}
	}
}

/*DEBUG COMMANDS*/
void	print_debug_command(t_cmd *cmd)
{
	int	i;
	int	number;

	number = 0;
	printf("DEBUG CONTENT:\n");
	while (cmd)
	{
		i = 0;
		if (cmd->argv[i])
		{
			printf("Command %d: ", number);
			while (cmd->argv[i])
			{
				printf("'%s' ", cmd->argv[i]);
				i++;
			}
		}
		printf("\n");
		number++;
		cmd = cmd->next;
	}
}
