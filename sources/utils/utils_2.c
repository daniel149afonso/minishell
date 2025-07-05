/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:52:22 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/05 07:54:00 by bullestico       ###   ########.fr       */
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
	int	idx;
	int	j;

	idx = 0;
	while (cmd)
	{
		j = 0;
		printf("[parse] commande %d :", idx++);
		while (cmd->argv && cmd->argv[j])
		{
			printf(" '%s'", cmd->argv[j]);
			j++;
		}
		printf("\n");
		printf("Infile: '%s'\n", cmd->infile);
		printf("Append: '%d'\n", cmd->append);
		printf("Heredoc: '%d'\n", cmd->heredoc);
		printf("Delimitor: '%s'\n", cmd->delimitor);
		printf("Outfile: '%s'\n", cmd->outfile);
		cmd = cmd->next;
	}
}
