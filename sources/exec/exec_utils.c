/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:00:49 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/25 21:06:11 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

void	free_n_exit_child(t_g *g, t_cmd *cmds, char **envp, int error_code)
{
	(void)cmds;
	if (g->cmds)
		free_cmds(g->cmds);
	if (g->lst)
		ft_lstclear(&g->lst, free);
	if (g->env)
		free_env(g->env);
	if (g->builtin)
		free(g->builtin);
	if (g->envbuilt)
		free(g->envbuilt);
	if (envp)
		free_split(envp);
	if (g->input)
		free(g->input);
	free(g);
	exit (error_code);
}

char	*ft_strjoin_free(char *s1, char *s2, int free_s1)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (free_s1)
		free(s1);
	return (res);
}
