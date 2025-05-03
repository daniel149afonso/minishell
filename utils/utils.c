/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:27:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/05/03 23:39:31 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_space(int c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
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

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*env = NULL;
}

char	*extract_check_key(char *str)
{
	if (!str)
		return (NULL);
	return (ft_substr(str, 0, ft_strlen(str)));
}

// static void	swap_env_nodes(t_env *a, t_env *b)
// {
// 	char	*tmp_key;
// 	char	*tmp_value;

// 	tmp_key = a->key;
// 	tmp_value = a->value;
// 	a->key = b->key;
// 	a->value = b->value;
// 	b->key = tmp_key;
// 	b->value = tmp_value;
// }

// void	f_bubblesort(t_list *lst)
// {
// 	t_env	*ptr;
// 	int		sorted;

// 	if (!env)
// 		return ;
// 	sorted = 0;
// 	while (!sorted)
// 	{
// 		sorted = 1;
// 		ptr = env;
// 		while (ptr && ptr->next)
// 		{
// 			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
// 			{
// 				swap_env_nodes(ptr, ptr->next);
// 				sorted = 0;
// 			}
// 			ptr = ptr->next;
// 		}
// 	}
// }
