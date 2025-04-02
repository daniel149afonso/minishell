/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:11:46 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/17 22:59:09 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned const char	*str;

	str = (unsigned const char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)str + i);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	const char	*str = "Hello";
	printf("%s\n", (unsigned char *)ft_memchr(str, 'e', 5));
	return (0);
}*/
//Elle permet de rechercher la première occurrence
//d'un caractère spécifique dans une zone de mémoire.
