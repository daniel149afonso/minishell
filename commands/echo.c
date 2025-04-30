/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:25:36 by daniel149af       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/29 17:31:01 by daafonso         ###   ########.fr       */
=======
/*   Updated: 2025/04/29 23:33:38 by daniel149af      ###   ########.fr       */
>>>>>>> 981d5bb1b09e6477ae51ed541e0ba43197973ffe
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// void	search_variable(char *path)
// {
// 	char	*equal_sign;
// 	int		len;

// 	len = ft_strlen(path);
// 	equal_sign = ft_strchr(path, '=');
// 	while (condition)
// 	{
// 		/* code */
// 	}

// }

void	search_puts_var(t_env *env, char *arg)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	int		found;

	key = extract_key(arg);
	value = extract_value(arg);
	if (!key || !value)
		return ;
	tmp = env;
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
	if (found)
		printf("%s", tmp->value);
	if (key)
		free(key);
	if (value)
		free(value);
}

int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

char	*extract_var_name(char *str, int *i)
{
	int		len;
	int		j;
	char	*name;

	len = 0;
	while (str[*i + len] && is_var_char(str[*i + len]))
		len++;
	name = malloc(len + 1);
	if (!name)
		return (0);
	j = 0;
	while (j < len)
	{
		name[j] = str[*i + j];
		j++;
	}
	name[j] = '\0';
	*i += len;
	return (name);
}

void	display_inside_quotes(t_g *g, char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			var = extract_var_name(str, &i);
			if (var)
			{
				search_puts_var(g->env, var);
				free(var);
			}
		}
		else
			write(1, &str[i++], 1);
	}
}

void	display_with_args(t_g *g, t_list *arg)
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
		display_inside_quotes(g, (char *)arg->content);
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
		display_with_args(g, arg);
	}
	else
		printf("\n");
	return ;
}
