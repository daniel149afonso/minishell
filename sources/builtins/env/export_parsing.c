/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:41:12 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/28 16:06:47 by apiscopo         ###   ########.fr       */
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

static void	print_error_env(char *value, t_list *tmp)
{
	value = extract_check_key(tmp->content);
	write(STDERR_FILENO, "minishell: export: `", 21);
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
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
	char	*tmp;
	int		return_code;

	return_code = 0;
	key = extract_key_concat((char *)arg);
	while (env)
	{
		if ((ft_strncmp(env->key, key, ft_strlen(key)) == 0))
		{
			value_next = extract_value((char *)arg);
			tmp = env->value;
			env->value = ft_strjoin(env->value, value_next);
			free(tmp);
			free(value_next);
			return_code = 1;
			return (free(key), return_code);
		}
		env = env->next;
	}
	return (free(key), return_code);
}

/*----------------------------------
vérifie si il y a possibilité de créé une variable
spécifiquement pour += ou l'update
----------------------------------*/
static void	check_concat(t_env *env, char *arg)
{
	int		i;
	char	*prmpt;
	char	*to_free;

	i = 0;
	prmpt = extract_check_key(arg);
	to_free = prmpt;
	while (prmpt[i] && prmpt[i + 1])
	{
		if (prmpt[i] == '+' && prmpt[i + 1] == '=')
		{
			free(to_free);
			prmpt = extract_key_concat(arg);
			to_free = prmpt;
			i = 0;
			if (update_env_value_concat(env, arg))
				return (free(to_free));
			add_env_node_concat(&env, arg);
			break ;
		}
		i++;
	}
	free(to_free);
}

/*----------------------------------
permet de check si un la commande
est bien écrite et si il faut += ou juste
ajouter ou update une variable
----------------------------------*/
int	check_if_var(t_env *env, t_list **lst)
{
	t_list	*arg;
	t_list	*tmp;
	char	*value;

	arg = *lst;
	tmp = *lst;
	while (tmp)
	{
		value = extract_check_key(tmp->content);
		if (value[0] == '=' || check_arg(value))
			return (print_error_env(value, tmp), free(value), 1);
		tmp = tmp->next;
		free(value);
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
