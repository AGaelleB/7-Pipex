# **7-Pipex**

Debut le 17 avril 2023

## **INTRODUCTION :**

Les pipes : les pipes sont des mécanismes de communication interprocessus (IPC) qui permettent de transférer le flux de données d'un processus à un autre. Dans le contexte de Pipex, je vais utiliser les pipes pour transférer le flux de données entre les deux fichiers et les deux commandes.

Les redirections : les redirections sont des opérations qui permettent de rediriger le flux d'entrée/sortie standard (stdin/stdout) d'un processus vers un fichier ou vers un autre processus. Dans le contexte de Pipex, je vais utiliser les redirections pour lire et écrire les données dans les fichiers.

Les processus : un processus est une instance d'un programme en cours d'exécution. Dans le contexte de Pipex, je vais utiliser plusieurs processus pour exécuter les différentes commandes et réaliser les différentes étapes du transfert de données entre les fichiers.

Le concept clé de Pipex est de réaliser le transfert de données entre deux fichiers en utilisant les pipes et les redirections pour connecter les différentes étapes du processus. 

## **COMMANDES :**

- PPID : $ echo "PID = $$; PPID = $PPID"
- Voir tous les processus actifs : $ ps -e
- Tuer les processus fils : int kill(pid_t pid, int sig);
    -> il faut ajouter la lib <signal.h> 
- Check your fds currently open : ls -la /proc/$$/fd
- Check whether the command exists and is executable : access()
- La fonction dup2() permet de rediriger les entrées/sorties standard d'un descripteur de fichier vers un autre descripteur. Voici sa syntaxe :



**=> TEST :**
valgrind --track-origins=yes --trace-children=yes --track-fds=yes --leak-check=full env -i ./pipex /dev/stdin "ls" "cat -e" /dev/stdout

Tester les cas classiques (fd NULL, n existe pas, pas les autorisations minimum, cmd pareil) e
Et les cas particuliers (surtout cat|cat|ls ou yes|head)


## **PIPE :**

En cas de succès, pipe renvoie 0. 
Par contre en cas d’échec, il renvoie -1, décrit l’erreur rencontrée dans errno, 
et ne remplit pas le tableau fourni.

0 = entre standard.
1 = sortie standard.
2 = sortie d'erreur.



## **FORK :**

La fonction fork() va dupliquer le processus courant. 
Lorsque l'ont va arriver au fork(), un nouveau processus identique au premier va être créer. C'est un peu comme si on se retrouvait a avoir lance deux fois le même programme. Sauf que fork() retourne un pid. 
Si le pid retourné est égal a 0, on est dans le processus qui vient d’être crée (processus fils). 
Sinon, le pid est égal au pid du processus fils.


