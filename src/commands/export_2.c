/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:41:12 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/04 22:14:55 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

char	*check_concat(t_env *env, t_list *arg)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = extract_check_key((char *)arg->content);
	while (key[i])
	{
		if (key[i] == '+' && key[i + 1] == '=')
		{
			value = extract_value((char *)arg->content);
			key = extract_key_concat((char*)arg->content);
			arg->content = ft_strjoin((char *)arg->content, value);
			update_or_add_var_concat(&env, arg->content);
			return (NULL);
		}
		i++;
	}
	return (arg->content);
}

void	check_if_var(t_env **env)
{
	t_list	*arg;
	t_list	*tmp;
	char	*value;

	arg = (*env)->lst->next;
	tmp = (*env)->lst->next;
	while(tmp)
	{
		value = extract_check_key(tmp->content);
		if (value[0] == '=' || check_arg(value))
			print_error_env(value, tmp);
		tmp = tmp->next;
	}
	if (!(arg->content = check_concat(*env, arg)))
		return ;
	while (arg)
	{
		update_or_add_var(env, (char *)arg->content);
		arg = arg->next;
	}
}
