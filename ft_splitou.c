/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitou.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:27:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/03/12 16:31:49 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft. h"

static char	**free_array(char **dest, int i)
{
	while (i > 0)
	{
		free(dest[--i]);
	}
	free(dest);
	return (0);
}

static int	count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

/*
		 /\_/\
		( o.o )
		 > ^ <
*/

static char	*strword(const char *start, const char *end)
{
	size_t	len;
	size_t	i;
	char	*str;

	len = end - start;
	i = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**splitword(const char *s, char c, char **dest)
{
	size_t		i;
	const char	*start;

	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			start = s;
			while (*s != '\0' && *s != c)
				s++;
			dest[i] = strword(start, s);
			if (dest[i] == NULL)
			{
				free_array(dest, i);
				return (NULL);
			}
			i++;
		}
		else
			s++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char		**dest;
	size_t		nbword;

	if (!s)
		return (NULL);
	nbword = count_word(s, c);
	dest = (char **)malloc((nbword + 1) * sizeof(char *));
	if (dest == NULL)
		return (NULL);
	dest = splitword(s, c, dest);
	return (dest);
}

/*#include <stdio.h>

int main() {
	char **result;
	size_t i;

	result = ft_split("hello world!", ' ');
	if (result) {
		for (i = 0; result[i] != NULL; i++) {
			printf("%s\n", result[i]);
			free(result[i]); // Libération de chaque chaîne
		}
		free(result); // Libération du tableau de pointeurs
	}
	return 0;
}
*/
