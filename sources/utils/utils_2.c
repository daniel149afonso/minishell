/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:52:22 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/26 19:03:50 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

/*DEBUG COMMANDS: REDIR INFILE, OUTFILE, APPEND: 
Pour chaque commande vérifie s'il est accompagné d'un fichier in, out ou append */
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
		//Check vers quel fichier chaque cmd est redirigé
		printf("Infile: '%s'\n", cmd->infile);
		printf("Append: '%d'\n", cmd->append);
		printf("Outfile: '%s'\n", cmd->outfile);
		cmd = cmd->next;
	}
}