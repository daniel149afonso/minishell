/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitou.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:27:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/05/29 15:23:06 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
			 /\_/\
			( o.o )
			 > ^ <
*/

//COMPLetement merdik
int	isstring(const char *s)
{
	int	i;
	int	trigger;

	trigger = 0;
	i = 1;
	if (s[i] == 34)
		return (2);
	while (s[i])
	{
		if (s[i] == 34)
		{
			trigger = 1;
			break ;
		}
		i++;
	}
	if (trigger == 0)
		return (1);
	if (i == 1)
		return (0);
	return (i + 1);
}

int	is_lococo(const char *s)
{
	int	len;

	len = 1;
	if ((s[0] == '<' && s[1] == '<') \
	|| (s[0] == '>' && s[1] == '>') \
	|| (s[0] == '<' && s[1] == '>'))
		len = 2;
	return (len);
}

static int	tokenize_2(const char *s, char **tokens)
{
	int	start;
	int	len;
	int	i;

	i = 0;
	start = 0;
	len = 0;
	if (ft_strchr("|;()<>", s[i]))
	{
		len = is_lococo(&s[i]);
		*(tokens) = ft_strndup(&s[i], len);
		if (!tokens)
			return (free_tokens(tokens), 0);
	}
	else
	{
		start = i;
		while (s[i] && !is_space(s[i]) && !ft_strchr("|;()<>", s[i]))
			i++;
		*(tokens) = ft_strndup(&s[start], i - start);
		if (!tokens)
			return (free_tokens(tokens), 0);
	}
	i += len;
	return (i);
}

//JFIGHT DES PTN DEMON  DAN MON CRANE FDP D INDEX Je vais normer un peu bb
char	**tokenize(const char *s, char **tokens)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		if (s[i] == '"')
		{
			len = isstring(&s[i]);
			if (len > 0)
				tokens[j] = ft_strndup(&s[i], len);
			j++;
		}
		else
			len = tokenize_2(&s[i], &tokens[j++]);
		i += len;
	}
	return (tokens[j] = NULL, tokens);
}

char	**ft_splitou(char const *s)
{
	char	**tokens;

	if (!s)
		return (NULL);
	tokens = malloc(1000 * sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens = tokenize(s, tokens);
	add_history(s);
	return (tokens);
}
/*        .--'''''''''--.
     .'      .---.      '.
    /    .-----------.    \
   /        .-----.        \
   |       .-.   .-.       |
   |      /   \ /   \      |
    \    | .-. | .-. |    /
     '-._| | | | | | |_.-'
         | '-' | '-' |
          \___/ \___/
       _.-'  /   \  `-._
     .' _.--|     |--._ '.
     ' _...-|     |-..._ '
            |     |
            '.___.'
              | |
             _| |_
            /\( )/\
           /  ` '  \
          | |     | |
          '-'     '-'
          | |     | |
          | |     | |
          | |-----| |
       .`/  |     | |/`.
       |    |     |    |
       '._.'| .-. |'._.'
             \ | /
             | | |
             | | |
             | | |
            /| | |\
          .'_| | |_`.
LGB       `. | | | .'
       .    /  |  \    .
      /o`.-'  / \  `-.`o\
     /o  o\ .'   `. /o  o\
     `.___.'       `.___.'

Fonction qui sers a split les commande plus le meta char ex:
"echo hahaha>output.txt"
result:
echo
hahaha
>
output.txt
/!\ MANQUE GESTION DE ""
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

//mange moi la queue Didi ptn avec des baguettes chinoises
