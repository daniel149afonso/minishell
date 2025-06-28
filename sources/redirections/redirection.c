/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/28 15:49:09 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Traite > stdout pour ajouter le contenu dans le fichier
(le contenu existant dans le fichier est ecrase), si une erreur return 1*/


/*Traite >> stdout pour ajouter a la suite du fichier, si une erreur return 1*/


/*Traite < stdin dirige le contenu d'un fichier vers stdin,
si erreur return 1*/


/*Cherche le type de redirection si une erreur return 1*/


int	validate_redirection_syntax(t_list *lst)
{
	if (parsing_redir(lst))
		return (0);
	return (1);
}

