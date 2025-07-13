/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:52:22 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/13 23:12:22 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if ((c >= '0' && c <= '9') || c == '_' || c == '?')
		return (1);
	return (0);
}

char	*ft_join_and_free(char *text, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(text, buffer);
	free(text);
	return (temp);
}

void	return_code(t_env *env, int error_code)
{
	env->error_code = error_code;
	env->var_error_code = error_code;
}

/*DEBUG COMMANDS: REDIR INFILE, OUTFILE, APPEND, HEREDOC, DELIMITOR*/
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
