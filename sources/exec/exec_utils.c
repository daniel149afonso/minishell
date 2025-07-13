/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:00:49 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/13 14:02:49 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	if (!cmds)
		return ;
	ft_free_redir(cmds->redirections);
	i = 0;
	while (cmds)
	{
		tmp = cmds->next;
		while (cmds->argv[i])
			free(cmds->argv[i++]);
		free(cmds);
		cmds = tmp;
	}
}

static int	for_envp(t_env *tmp)
{
	int	count;

	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**get_envp_array(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		count;
	int		i;

	tmp = env;
	count = for_envp(tmp);
	i = 0;
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin_free(envp[i], tmp->value, 1);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*ft_strjoin_free(char *s1, char *s2, int free_s1)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (free_s1)
		free(s1);
	return (res);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}
