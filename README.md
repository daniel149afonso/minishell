<img width="2146" height="548" alt="grafik" src="https://github.com/user-attachments/assets/a2c1ab2f-e400-4a51-821e-83d4aa32e511" />


<img width="664" alt="image" src="https://github.com/user-attachments/assets/a12918ec-35e3-4e41-a5ef-8780b92c3364" />


# Commandes status:

## infos à jour:

TOUT MARCHE INSHALLAH

echo salut > test.txt > out.txt | pwd | cat << st | echo bonjour | cd | export a=323 | env | pwd > out.txt | << st | echo bonjour


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

export ARGS += ✅

test finaux de export ✅

# Ordre de travail:
Termine les builtins simples

Implémente la redirection > : echo salut > test.txt, echo salut>test.txt
si le fichier n'existe pas le creer
commande > fichier        # redirige la sortie
commande >> fichier       # append à un fichier
commande < fichier        # lit depuis un fichier

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
