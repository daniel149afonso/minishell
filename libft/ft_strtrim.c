/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:27:19 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/18 19:22:57 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
	{
		start++;
	}
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
	{
		end--;
	}
	len = end - start;
	return (ft_substr(s1, start, len));
}

/*int	main(void)
{
	char	*str = "wswArya Starkwsws";
	char	*ocur = "ws";
	char	*result;

	result = ft_strtrim(str, ocur);
	printf("String: %s\n", result);
	free(result);
	return (0);
}*/
// BUT: Ft_strtrim supprime les caracteres avant du debut et de la fin de s1
// qui sont present dans set.
// Cas particulier: start > end
// donc tous les caracteres de s1 sont presents dans set
// donc tous a supprimer resultat final une chaine vide
//(size_t)-1 == SIZE_MAX
