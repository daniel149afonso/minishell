/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:15:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/07/05 01:44:10 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Check si la variable existe dans l'env, si oui elle l'expanse
sinon elle est traitée comme une string normale*/
void	handle_variable_expansion(char *str, char **res, int *i, t_env *env)
{
	char	*var;
	char	*val;

	(*i)++;
	val = NULL;
	var = extract_var_name(str, i);
	if ((ft_strncmp(var, "?", ft_strlen(var))) == 0)
	{
		*res = ft_itoa(env->var_error_code);
		free(var);
		return ;
	}
	val = get_env_value(env, var);
	if (val)
		*res = ft_join_and_free(*res, val);
	free(val);
	free(var);
}

/*Reconstruis la string en ajoutant char par char*/
void	add_char_to_result(char *str, char **res, int *i)
{
	char	c[2];

	c[0] = str[*i];
	c[1] = '\0';
	*res = ft_join_and_free(*res, c);
	(*i)++;
}

/*Cherche une variable qui commence par $ entre double quotes ou non
mais ne fait rien si elle est entre single quote*/
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

/*Parcours chaque token pour chercher s'il y a une variable*/
char	**search_var(char **strs, t_env *env)
{
	int		i;
	char	*var;

	i = 0;
	if (!env)
		return (strs);
	while (strs[i])
	{
		var = expand_variables(strs[i], env);
		free(strs[i]);
		strs[i] = var;
		i++;
	}
	return (strs);
}
