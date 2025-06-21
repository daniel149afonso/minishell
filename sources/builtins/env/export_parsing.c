/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:41:12 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/21 20:26:33 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*						UTILS						 */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int	check_arg(char *value)
{
	if (ft_isalpha(value[0]) || value[0] == '_')
		return (0);
	return (1);
}

static void    print_error_env(char *value, t_list *tmp)
{
	value = extract_check_key(tmp->content);
	printf("export: `%s': not a valid identifier\n", value);
	free(value);
	return ;
}

/*----------------------------------
Update s'il le faut, une variable +=
----------------------------------*/
static int	update_env_value_concat(t_env *env, char *arg)
{
	char	*key;
	char	*value_next;
	int		return_code;

	return_code = 0;
	key = extract_key_concat((char *)arg);
	while (env)
	{
		if ((ft_strncmp(env->key, key, ft_strlen(key)) == 0))
		{
			value_next = extract_value((char *)arg);
			env->value = ft_strjoin(env->value, value_next);
			free(value_next);
			return_code = 1;
			return (return_code);
		}
		env = env->next;
	}
	return (return_code);
}

/*----------------------------------
vérifie si il y a possibilité de créé une variable
spécifiquement pour += ou l'update
----------------------------------*/
static void	check_concat(t_env *env, char *arg)
{
	int		i;
	char	*prmpt;

	i = 0;
	prmpt = extract_check_key(arg);
	while(prmpt[i])
	{
		if (prmpt[i] == '+' && prmpt[i + 1] == '=')
		{
			prmpt = extract_key_concat(arg);
			if (update_env_value_concat(env, arg))
				return ;
			add_env_node_concat(&env, arg);
		}
		i++;
	}
}

/*----------------------------------
permet de check si un la commande
est bien écrite et si il faut += ou juste
ajouter ou update une variable
----------------------------------*/
int	check_if_var(t_env *env)
{
	t_list	*arg;
	t_list	*tmp;
	char	*value;

	arg = env->lst->next;
	tmp = env->lst->next;
	while (tmp)
	{
		value = extract_check_key(tmp->content);
		if (value[0] == '=' || check_arg(value))
		{
			print_error_env(value, tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	while (arg)
	{
		if (ft_strchr(arg->content, '+'))
			check_concat(env, (char *)arg->content);
		else
			update_or_add_var(&env, (char *)arg->content);
		arg = arg->next;
	}
	return (0);
}
