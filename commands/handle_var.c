/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:15:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/04/30 20:17:08 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


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

void	search_puts_var(t_env *env, char *arg)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	int		found;

	printf("Before name: %s\n", arg);
	key = extract_key(arg);
	value = extract_value(arg);
	printf("key: %s, value: %s\n", key, value);
	if (!key || !value)
	{
		printf("key or value does not exist\n");
		return ;
	}
	tmp = env;
	found = 0;
	printf("DEBUG | looking for: %s\n", key);
	while (tmp)
	{
		printf("DEBUG | checking key: %s\n", tmp->key);
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
