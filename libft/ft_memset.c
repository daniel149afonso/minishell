/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:53:04 by marvin            #+#    #+#             */
/*   Updated: 2024/10/02 12:53:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/*int	main(void)
{
	char	str[8];

	ft_memset(str, 'B', 8);
	for (int i = 0; i < 8; i++)
	{
        	printf("%c ", str[i]);
	}
	printf("\n");
	return (0);
}*/
//BUT: remplir une zone mémoire avec une valeur spécifique
