/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:05:39 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/12 17:34:14 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(long nbr, char *str, size_t len)
{
	size_t			i;
	unsigned int	is_neg;

	is_neg = 0;
	i = len;
	if (nbr < 0)
	{
		is_neg++;
		nbr = -nbr;
	}
	str[i] = '\0';
	while (i > is_neg)
	{
		i--;
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (is_neg == 1)
		str[0] = '-';
	return (str);
}

static size_t	int_length(long nbr)
{
	size_t	count;

	count = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		count++;
	}
	else if (nbr == 0)
		count++;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	nbr;
	char	*str;

	nbr = (long)n;
	len = int_length(nbr);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_convert(nbr, str, len);
	return (str);
}

/*int	main(void)
{
	long int	nbr = -2147000;
	char *result = ft_itoa(nbr);
	printf("Taille: %zu\n", int_length(nbr));
	printf("%s\n", result);
	free(result);
	return (0);
}*/
