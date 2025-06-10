/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitou.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:27:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/09 22:17:03 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
/*
			 /\_/\
			( o.o )
			 > ^ <
*/
int	redir_len(const char *s)
{
	if ((s[0] == '<' && s[1] == '<')
		|| (s[0] == '>' && s[1] == '>')
		|| (s[0] == '<' && s[1] == '>'))
		return (2);
	return (1);
}

int	read_word(const char *s, int *pos, char **out)
{
	int		start;
	int		i;
	char	q;

	start = *pos;
	i = start;
	while (s[i])
	{
		if (is_space(s[i]) || ft_strchr("|;()<>", s[i]))
			break ;
		if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i++];
			while (s[i] && s[i] != q)
				i++;
			if (s[i] == q)
				i++;
		}
		else
			i++;
	}
	*out = ft_strndup(&s[start], i - start);
	if (!*out)
		return (0);
	*pos = i;
	return (1);
}

char	*get_next_token(const char *s, int *i)
{
	char *tok;
	int len;

	if (ft_strchr("|;()<>", s[*i]))
	{
		len = redir_len(&s[*i]);
		tok = ft_strndup(&s[*i], len);
		*i += len;
	}
	else
	{
		if (!read_word(s, i, &tok))
			return NULL;
	}
	return (tok);
}

char	**ft_splitou(const char *s)
{
	char	**tokens;
	int		i;
	int		j;
	char	*tok;

	if (!s)
		return (NULL);
	tokens = malloc(1000 * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		if (!s[i])
			break ;
		tok = get_next_token(s, &i);
		if (!tok)
			return (free_tokens(tokens), NULL);
		tokens[j++] = tok;
	}
	tokens[j] = NULL;
	add_history(s);
	return (tokens);
}
/*
Fonction qui sers a split les commande plus le meta char ex:
"echo hahaha>output.txt"
result:
echo
hahaha
>
output.txt
#include <stdio.h>

int main() {
	char **result;
	size_t i;

	result = ft_split("echo<ls|cat -e|ls");
	if (result) {
		for (i = 0; result[i] != NULL; i++) {
			printf("%s\n", result[i]);
			free(result[i]);
		}
		free(result);
	}
	return 0;
}*/
