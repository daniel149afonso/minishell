/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:19:33 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/18 19:35:25 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	s2 = malloc((i + 1) * sizeof(char));
	if (!s2)
		return (0);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/*int	main(void)
{
	char	str[] = "Hello";
	char	*result = ft_strdup((const char *)str);
	printf("%s\n", result);
	free(result);
	return (0);
}*/
//BUT: créer une copie d'une chaîne de caractères.
//Elle alloue dynamiquement la mémoire nécessaire
//pour contenir la chaîne d'origine
