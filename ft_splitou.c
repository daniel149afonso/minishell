/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitou.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:27:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/03/12 21:29:17 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int metachar(char c)
{
	if (c == '|' || c == ';' || c == '(' || c == ')' ||
		c == '<' || c == '>')
		return (0);
	else
		return (1);
}

/*
			 /\_/\
			( o.o )
			 > ^ <
*/

void free_tokens(char **tokens, size_t count) {
    for (size_t i = 0; i < count; i++)
        free(tokens[i]);
    free(tokens);
}

char	**tokenize(const char *s, char **tokens)
{
	int i = 0;
	int j = 0;
	int	len = 0;
	int	start = 0;
	
	while (s[i])
	{
		while (isspace(s[i]))
			i++;
		if (!s[i])
			break;
		if (strchr("|;()<>", s[i]))
		{
			len = 1;
			if ((s[i] == '<' && s[i + 1] == '<') ||
				(s[i] == '>' && s[i + 1] == '>') ||
				(s[i] == '<' && s[i + 1] == '>'))
			{
				len = 2;
			}
			tokens[j] = strndup(&s[i], len);
			if (!tokens[j])
			{
				free_tokens(tokens, j);
				return NULL;
			}
			j++;
			i += len;
		}
		else
		{
			start = i;
			while (s[i] && !isspace(s[i]) && !strchr("|;()<>", s[i]))
				i++;
			tokens[j] = strndup(&s[start], i - start);
			if (!tokens[j])
			{
				free_tokens(tokens, j);
				return NULL;
			}
			j++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

char	**ft_splitou(char const *s)
{
	char **tokens;

	if (!s)
		return (NULL);
	tokens = malloc(500 * sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens = tokenize(s, tokens);
	return (tokens);
}
/*
#include <stdio.h>

int main() {
	char **result;
	size_t i;

	result = ft_split("echo<ls|cat -e|ls");
	if (result) {
		for (i = 0; result[i] != NULL; i++) {
			printf("%s\n", result[i]);
			free(result[i]); // Libération de chaque chaîne
		}
		free(result); // Libération du tableau de pointeurs
	}
	return 0;
}*/

//mange moi la queue Didi ptn
