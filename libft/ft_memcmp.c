/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:05:01 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/18 18:11:27 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_memcmp("ac", "ab", 2));
	return (0);
}*/
//BUT: Elle compare deux blocs de mémoire octet par octet et renvoie un entier
//indiquant si les blocs sont identiques ou,
//si ce n'est pas le cas, lequel des deux est plus grand(la difference des deux)
//s1 : Un pointeur vers le premier bloc de mémoire à comparer.
//s2 : Un pointeur vers le deuxième bloc de mémoire à comparer.
//n : Le nombre d'octets à comparer.
