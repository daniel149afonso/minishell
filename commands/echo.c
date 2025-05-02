/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:25:36 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/30 16:20:29 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	display_content(t_list *arg)
{
	while (arg && arg->content)
	{
		printf("%s", (char *)arg->content);
		if (arg->next && arg->next->content)
			printf(" ");
		arg = arg->next;
	}
}
/*
void	search_variable(char *path)
{
	char	*equal_sign;
	int		len;

	len = ft_strlen(path);
	equal_sign = ft_strchr(path, '=');
	while (condition)
}
*/

void	update_or_add_var(t_env **env, char *arg)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	//int		found;

	key = extract_key(arg);
	value = extract_value(arg);
	tmp = *env;
	//found = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = value;
			//found = 1;
			break ;
		}
		tmp = tmp->next;
	}
	// if (!found)
	// 	add_env_node(env, arg);
	// free(key);
	// if (!found)
	// 	free(value);
}

void	display_inside_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			// On saute le caractère de quote
			i++;
			continue ;
		}
		write(1, &str[i], 1);
		i++;
	}
}

void	display_with_args(t_list *arg)
{
	int		newline;

	newline = 1;
	while (arg && arg->content && ft_strcmp((char *)arg->content, "-n") == 0)
	{
		arg = arg->next;
		newline = 0;
	}
	while (arg && arg->content)
	{
		display_inside_quotes((char *)arg->content);
		arg = arg->next;
		if (arg && arg->content)
			printf(" ");
	}
	if (newline)
		printf("\n");
}

void	ft_echo(t_g *g)
{
	t_list	*arg;

	arg = g->lst->next;
	if (arg && arg->content)
	{
		display_with_args(arg);
	}
	else
		printf("\n");
	return ;
}
