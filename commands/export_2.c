/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:41:12 by apiscopo          #+#    #+#             */
/*   Updated: 2025/05/02 20:48:36 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	check_arg(char *value)
{
	if (ft_isalpha(value[0]) || value[0] == '_')
		return (0);
	return (1);
}

static void    print_error_env(char *value, t_list *tmp)
{
    printf("export: `%s': not a valid identifier\n", value);
	tmp = tmp->next;
	while (tmp)
	{
		value = extract_check_key(tmp->content);
		printf("export: `%s': not a valid identifier\n", value);
		tmp = tmp->next;
	}
	return ;
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
	while (arg)
	{
		update_or_add_var(env, (char *)arg->content);
		arg = arg->next;
	}
}
