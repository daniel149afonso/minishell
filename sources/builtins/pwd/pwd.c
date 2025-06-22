/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:10:10 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/21 20:32:24 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*Recupere le chemin actuel et l'affiche*/
int	ft_pwd(t_g *g)
{
	char	buffer[1024];

	(void)g;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
	{
		perror("Error, pwd");
		return (1);
	}
	return (0);
}
