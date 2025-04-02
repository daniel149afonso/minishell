/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:06 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/18 19:21:28 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*char	ft_toupper_v2(unsigned int i, char c)
{
	// On ignore l'indice
	(void)i;
	// Conversion en majuscule
	return ((char)ft_toupper(c));
}

int	main(void)
{
	const char	str[] = "John Snow";
	char	*result = ft_strmapi(str, ft_toupper_v2);
	printf("%s\n", result);
	free(result);
	return (0);
}*/
//BUT: Applique une fonction à chaque caractère
//d'une chaîne et renvoie une nouvelle chaîne.
//toupper est modifie pour ignorer i
