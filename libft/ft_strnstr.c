/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:13:32 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/18 19:22:39 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] && needle[j] && (i + j) < len
			&& haystack[i + j] == needle[j])
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
		j = 0;
	}
	return (NULL);
}

/*int	main(int argc, char **argv)
{
	if (argc == 3)
		printf("%s\n", ft_strnstr(argv[1], argv[2], 1));
	return (0);
}*/
//BUT: recherche une sous-chaîne dans une chaîne principale,
//en limitant le nombre de caractères à inspecter
