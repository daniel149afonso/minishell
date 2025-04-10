/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:03:40 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/18 19:36:34 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_total;

	len_total = ft_strlen(s1);
	len_total += ft_strlen(s2);
	str = malloc(sizeof(char) * (len_total + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len_total + 1);
	ft_strlcat(str, s2, len_total + 1);
	return (str);
}

/*int	main(void)
{
	const char	str[] = "Arya";
	const char	str1[] = " Stark";
	char	*result = ft_strjoin(str, str1);
	//+1 apres len pour inclure espace char '\0'
	printf("%s\n", result);
	free(result);
	return (0);
}*/
// Concatene deux string dans une nouvelle string alloue dynamiquement
