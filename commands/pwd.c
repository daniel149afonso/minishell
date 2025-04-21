/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:10:10 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/21 22:10:43 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_pwd(t_list *lst)
{
	char	buffer[1024];

	(void)lst;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
		perror("Error, pwd");
}