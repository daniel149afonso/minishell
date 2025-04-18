# Commandes status:
cd (changement de dossier - Daniel): changer la var d'environnement PWD et OLD_PWD a chaque appel

pwd (très simple - Daniel): ✅

echo (facile, bon exercice sur les arguments - Daniel)

exit (important pour gérer la fin de minishell - Alessio)

env (juste afficher l’environnement - Alessio) ✅
3

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
