# Commandes status:

## cd (changement de dossier - Daniel): ✅

gestion de dossier✅

gestion de OLD_PWD et PWD✅

## pwd (très simple - Daniel): ✅

## echo (facile, bon exercice sur les arguments - Daniel) 

gestion des quotes, variables ✅

## exit (important pour gérer la fin de minishell - Alessio) ✅

gestion de Ctl+D ✅

gestion de input "exit" ✅

0 leaks (sauf readline) ✅

## env (juste afficher l’environnement - Alessio) ✅

mise a jour de l'env ✅

tests finaux ✅

## export / unset (un peu plus complexes : manipuler envp)

export ✅

unset ✅

export ARGS ✅

export ARGS unindentified ✅

export ARGS +=

test finaux de export 

# Ordre de travail:
Termine les builtins simples

Implémente la redirection >

Ensuite les pipes

Enfin les cas mixtes + bonus(oublie les bonus daniel) (<<, gestion des quotes, etc.)

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
