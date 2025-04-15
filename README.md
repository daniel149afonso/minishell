# Commandes status:
cd (en cours - Daniel): manque gestion si HOME n'existe pas

pwd (très simple - Daniel): fini

echo (facile, bon exercice sur les arguments - a voir?)

exit (important pour gérer la fin de minishell - Alessio)

env (juste afficher l’environnement - Alessio)

export / unset (un peu plus complexes : manipuler envp)

# Ordre de travail:
Termine les builtins simples

Implémente la redirection >

Ensuite les pipes

Enfin les cas mixtes + bonus (<<, gestion des quotes, etc.)

# Arguments pour chaque commande
✅ pwd

    Elle n’a pas besoin d’arguments

    Elle n’a pas besoin de modifier l’environnement

    → Tu peux la déclarer comme (void)
✅ cd
    Elle a besoin de l’argument du chemin → dans lst->next

    Elle n’a pas besoin de l’environnement pour l’instant

    → Tu peux passer t_list *lst

✅ export, unset

    Elles doivent modifier l’environnement

    Donc tu dois leur passer quelque chose comme char ***envp

✅ Commandes externes (non-builtin)

    Tu auras besoin de :

        La commande (char *cmd)

        Les arguments (char **argv)

        L’environnement (char **envp)

        Peut-être des infos de redirections
