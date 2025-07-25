/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:27:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/25 00:50:29 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_space(int c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	env = NULL;
}

char	*extract_check_key(char *str)
{
	if (!str)
		return (NULL);
	return (ft_substr(str, 0, ft_strlen(str)));
}

void	swap_env_content(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	f_bubblesort(t_env *head)
{
	int		sorted;
	t_env	*current;

	if (!head)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = head;
		while (current && current->next)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				swap_env_content(current, current->next);
				sorted = 0;
			}
			current = current->next;
		}
	}
}
