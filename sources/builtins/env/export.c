/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:51:01 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/25 20:51:24 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*						UTILS						 */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
char	*extract_key(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*extract_value(char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*---------------------------
Fonction qui sert a update une variable déja existante
ou la créé sans la version +=
---------------------------*/
void	update_or_add_var(t_env **env, char *arg)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	int		found;

	key = extract_key(arg);
	value = extract_value(arg);
	tmp = *env;
	found = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = value;
			found = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!found)
		add_env_node(env, arg);
	free(key);
	if (!found)
		free(value);
}

static int	f_redirec(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp && tmp->content)
	{
		if (!right_redir(lst) || !left_redir(lst))
			return (1);
	}
	return (0);
}

/*---------------------------
Fonction de base export qui va 
écrire les variables existante si aucun argument
ou va allez update les variables avec "check_if_var"
---------------------------*/
int	ft_exp(t_env *env, t_list *lst)
{
	t_env	*tmp;

	tmp = env;
	if (!lst || !lst->next || f_redirec(lst))
	{
		f_bubblesort(tmp);
		while (tmp)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
			tmp = tmp->next;
		}
	}
	else
	{
		if (check_if_var(env, lst))
			return (1);
		return (0);
	}
	return (0);
}
