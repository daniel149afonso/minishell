/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:36:30 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/01 20:21:19 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}
/*
int main(int argc, char **argv)
{
	if (argc == 2 && argv[1][1] == '\0')
	{
		printf("%d\n", ft_isalnum(argv[1][0]));
	}
	return (0);
}*/
