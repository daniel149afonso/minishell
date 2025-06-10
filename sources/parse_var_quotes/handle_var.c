/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:15:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/06/04 22:13:29 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

void	add_char_to_result(char *str, char **res, int *i)
{
	char	c[2];

	c[0] = str[*i];
	c[1] = '\0';
	*res = ft_join_and_free(*res, c);
	(*i)++;
}

char	*expand_variables(char *str, t_env *env)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*res;

	i = 0;
	in_single = 0;
	in_double = 0;
	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '$' && !in_single)
		{
			handle_variable_expansion(str, &res, &i, env);
			continue ;
		}
		add_char_to_result(str, &res, &i);
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
