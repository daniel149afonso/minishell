/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:37:28 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/18 19:29:14 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result *= sign);
}

/*int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%d\n", ft_atoi(argv[1]));
	return (0);
}*/
/*
BUT: Convertit une chaîne de caractères en un entier.
Elle ignore les espaces blancs au début de la chaîne,
 traite les signes (positif ou négatif),
  et convertit la séquence numérique en entier
*/
