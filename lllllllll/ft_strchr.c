/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:16:56 by daniel149af       #+#    #+#             */
/*   Updated: 2024/10/17 13:50:58 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	cc;

	i = 0;
	cc = (char)c;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

/*int	main(void)
{
	char	str[] = "Morty";
	int	c = 1024;
	printf("%s", ft_strchr(str, c));
	return (0);
}*/
//Trouve le premier caractère dans une chaîne
//Si Trouve: Return un pointeur sur le premier caractere
//Si c == '\0' Return un pointeur vers la fin de la chaine
//Si rien trouve return NULL
//Conversion int en char -128 et 127 (valeurs char)
