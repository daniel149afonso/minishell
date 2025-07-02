/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:00:49 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/02 18:01:25 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void free_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	while (cmds)
	{
		tmp = cmds->next;
		
		while (cmds->argv[i])
			free(cmds->argv[i++]);
		free(cmds->argv);
		free(cmds->infile);
		free(cmds->outfile);
		free(cmds);
		cmds = tmp;
	}
}

char **get_envp_array(t_env *env)
{
	int count = 0;
	t_env *tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}

	char **envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return NULL;

	tmp = env;
	int i = 0;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin_free(envp[i], tmp->value, 1);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return envp;
}

char *ft_strjoin_free(char *s1, char *s2, int free_s1)
{
	char *res = ft_strjoin(s1, s2);
	if (free_s1)
		free(s1);
	return res;
}

void free_split(char **arr)
{
	int i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}