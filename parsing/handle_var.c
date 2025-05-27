/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:15:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/05/26 20:55:33 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	handle_single_quote(char *str, char **res, int *i, int *in_single)
{
	char	c[2];

	*in_single = !(*in_single);
	c[0] = str[*i];
	c[1] = '\0';
	*res = ft_join_and_free(*res, c);
	(*i)++;
}

void	handle_variable_expansion(char *str, char **res, int *i, t_env *env)
{
	char	*var;
	char	*val;

	(*i)++;
	var = extract_var_name(str, i);
	val = get_env_value(env, var);
	if (val)
		*res = ft_join_and_free(*res, val);
	free(var);
}

char	*expand_variables(char *str, t_env *env)
{
	int		i;
	int		in_single;
	char	*res;
	char	c[2];

	i = 0;
	in_single = 0;
	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			handle_single_quote(str, &res, &i, &in_single);
		else if (str[i] == '$' && !in_single)
			handle_variable_expansion(str, &res, &i, env);
		else
		{
			c[0] = str[i];
			c[1] = '\0';
			res = ft_join_and_free(res, c);
			i++;
		}
	}
	return (res);
}


char	**search_var(char **strs, t_env *env)
{
	int		i;
	char	*var;

	i = 0;
	while (strs[i])
	{
		var = expand_variables(strs[i], env);
		free(strs[i]);
		strs[i] = var;
		i++;
	}
	return (strs);
}
