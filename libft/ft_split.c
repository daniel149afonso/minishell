/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:59:32 by daafonso          #+#    #+#             */
/*   Updated: 2024/10/18 17:58:25 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freeall(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	word_count(const char *s, char c)
{
	size_t	i;
	size_t	count_word;
	size_t	last_sep;

	i = 0;
	count_word = 0;
	last_sep = 1;
	while (s[i])
	{
		if (s[i] != c && last_sep == 1)
		{
			last_sep = 0;
			count_word++;
		}
		else if (s[i] == c)
			last_sep = 1;
		i++;
	}
	return (count_word);
}

static char	*fill_word(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[i] && j < word_count(s, c))
	{
		if (s[i] != c)
		{
			str[j] = fill_word(s + i, c);
			if (!str[j])
				return (ft_freeall(str), NULL);
			i = i + ft_strlen(str[j]);
			j++;
		}
		else
			i++;
	}
	str[j] = NULL;
	return (str);
}

/*int	main(void)
{
	size_t	i;
	char	*str = " Arya Stark: Winter is coming";
	char	sep = ' ';
	char	**result;

	i = 0;
	result = ft_split(str, sep); //tableau de string
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		free(result[i]); //libere chaque string
		i++;
	}
	free(result); //libere le tableau entier de string
	return (0);
}*/
//BUT: Decoupe un string en un tableau de string
// s = string, c = delimiteur
//Return un tableau de string
//FT_FREE:
//En cas de mauvaise alloc libere les string du tableau et le tableau lui meme
//WORD_COUNT:
//Cette fonction compte le nombre de mots
//dans la chaîne s en fonction du caractère séparateur c
//FILL_WORD:
//Cette fonction extrait un mot de la chaîne s
//en commençant à un point donné jusqu'à ce qu'elle rencontre le séparateur c
//LA PREMIERE BOUCLE WHILE compte le nombre de caractères
//jusqu'à ce que le séparateur soit atteint
//ou que la fin de la chaîne soit rencontrée.
//UNE SECONDE BOUCLE WHILE copie les caractères de s
//dans buffer jusqu'à ce que le séparateur soit atteint.
//FT_SPLIT:

// La première étape consiste à allouer de
//la mémoire pour le tableau str en fonction du nombre de mots
// Si l'allocation échoue, la fonction retourne NULL.
// La boucle while continue jusqu'à la fin de la chaîne s
// ou jusqu'à ce que tous les mots soient ajoutés au tableau.
// Si le caractère actuel s[i] n'est pas un séparateur (c),
// cela indique le début d'un mot.
// La fonction fill_word est appelée pour extraire le mot à partir de s[i].
// Si fill_word retourne NULL (échec d'allocation),
//  la fonction appelle ft_freeall pour libérer la mémoire précédemment allouée
//  et retourne NULL.
// i est ensuite mis à jour en ajoutant la longueur du mot extrait,
// et j est incrémenté pour passer au prochain emplacement dans le tableau.
// Si s[i] est un séparateur,
// i est simplement incrémenté pour passer au caractère suivant.
//ATTENTION:
//fill_word(s + i, c)
//Pointe vers la premiere lettre trouvee d'un mot
//ATTENTION:
//i = i + ft_strlen(str[j])
//Cela met à jour l'index i pour qu'il pointe vers le caractère suivant
//après le mot extrait. En d'autres termes, après avoir extrait un mot,
// i est déplacé au-delà de ce mot afin que la prochaine itération de la boucle
//commence à partir du caractère suivant.
