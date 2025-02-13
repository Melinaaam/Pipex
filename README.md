# 🇬🇧 Pipex : |

```
./pipex	Infile "cmd1" "cmd2" Outfile
allows you to simulate the following operation :
cat infile | cmd1 | cmd2 > outfile

Pipe()
|
|
|-------pid1 = fork();
|	|
|	|
|	|-------------first_child;//cmd1
|			|
|			|--dup2();
|			|--excecve(path,**string_av, **env);
|-------pid2 = fork();
|	|
|	|
|	|--------------second_child;//cmd2
|			|
|			|--dup2();
|			|--excecve(path,**string_av, **env);
|
|
|-------waitpid;//pid1
|-------waitpid;//pid2

```


## Undersatnd Unix processes in C : video
```
https://www.youtube.com/watch?v=tcYo6hipaSA&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=2
```

## Processus
A processus is a copy of a program that is running.
A program is just file on the computer that does nothing until it is started. A process is the same program but once it is launched. When it is launched, the operating system gives it a unique identifier: PID (Process ID). This identifier allows the system to know which process is doing what.

A pipe is a mechanism for "connecting communication" directly between processes, so that the output of one process (stdout) directly feeds the input (stdin) of the next. The pipe is widely used on Unix, for example to associate several commands whose processing is chained.

In Unix-like operating systems, every process except process 0 (the swapper) is created when another process executes the fork() system call. The process that invoked fork is the parent process and the newly created process is the child process. Every process (except process 0) has one parent process, but can have many child processes.

To reproduce the operation of the pipe, we will need to know certain functions :

- Pipe
- fork
- dup2
- excecve
- waitpid

* Pipe : int pipe (pipefd[])

creates a communication channel between two processes.

He create 2 file descriptor :
pipefd[0] : read in the pipe
pipefd[1] : write in the pipe

* fork() :

creates a child processs by duplicating he current process.
The current process continu his execution and the child process  execute his execution.

The parent proess receive the PID of the child process as return from fork and the child process receive 0 as return from fork.

* excecve() :

Replace the current process by a new rogram.

It use by the child process after call from fork, for executing a command.
He takes 3 av :
	- the ath of the command
	- a sring area who repreen argumets of the command
	- a string area of the environement

Excecve never return expet error

* dup2() :

dulicate a file descriptor to replace it with another. Useful for redirecting standard inputs and outputs.

dup2(pipefd[1], STDOUT_FILENO)
redirects standard output to the write pipe.

* waitpid() :

In computer operating systems, a process (or task) may wait for another process to complete its execution.
In most systems, a parent process can create an independently executing child process.
The parent process may then issue a wait system call, which suspends the execution of the parent process while the child executes.
When the child process terminates, it returns an exit status to the operating system, which is then returned to the waiting parent process.
The parent process then resumes execution.[1]

## Test Ideas for Pipex

1. **Basic Test: Simple Redirection**
   - **Command:**
     ```bash
     ./pipex infile "cat" "wc -l" outfile
     ```
   - **Verification:**
     The `outfile` file should contain the number of lines from `infile`.

2. **Test with Invalid Command**
   - **Command:**
     ```bash
     ./pipex infile "invalid_command" "wc -l" outfile
     ```
   - **Verification:**
     The program should handle the error and display a clear message without crashing.

3. **Permissions Test on Files**
   - **Case:**
     Provide a non-existent input file or an output file in a directory where the user does not have write permissions.
   - **Verification:**
     The program should report a read or write error accordingly.

4. **Test with Multiple Chained Commands**
   - **Command:**
     Try simple commands like `"grep"` and `"sort"`.
     ```bash
     ./pipex infile "grep pattern" "sort" outfile
     ```
   - **Verification:**
     The `outfile` file should contain the sorted lines that match the searched pattern from `infile`.

5. **Edge Case Tests**
   - **Case:**
     Test with large files or commands that produce a substantial amount of output.
   - **Verification:**
     Make sure there are no memory leaks and that the redirection is performed correctly.

# 🇫🇷 Pipex : |

Ce projet recrée le comportement d'une chaîne de pipes en Unix, permettant d'exécuter deux commandes consécutives avec redirection d'entrée et de sortie.
Par exemple, l'exécution :

```
./pipex infile "cmd1" "cmd2" outfile
permet de simuler l'opération suivante :
cat infile | cmd1 | cmd2 > outfile


Pipe()
   │
   ├── pid1 = fork();
   │      │
   │      └── first_child; // Exécute cmd1
   │             │
   │             ├── dup2();  // Redirige l'entrée/sortie
   │             └── execve(path, **string_av, **env);
   │
   ├── pid2 = fork();
   │      │
   │      └── second_child; // Exécute cmd2
   │             │
   │             ├── dup2();  // Redirige l'entrée/sortie
   │             └── execve(path, **string_av, **env);
   │
   └── waitpid(); // Attend la fin des deux processus enfants
```

## Vidéo d'Introduction aux Processus Unix en C

Pour comprendre le fonctionnement des processus Unix, regardez cette vidéo :
```
https://www.youtube.com/watch?v=tcYo6hipaSA&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=2
```

## Processus

Un processus est une instance en exécution d'un programme.

    Un programme est un fichier qui ne fait rien tant qu'il n'est pas lancé.
    Lorsqu'il est lancé, le système d'exploitation crée un processus et lui attribue un identifiant unique (PID), permettant de suivre son exécution.

Pour reproduire le fonctionnement du pipe, nous avons besoin de connaitre certaines fonctions :

- Pipe
- fork
- dup2
- excecve
- waitpid

Pipe : int pipe (pipefd[])

Un pipe est un mécanisme permettant de connecter la sortie standard (stdout) d'un processus à l'entrée standard (stdin) d'un autre.

    La fonction pipe(pipefd) crée deux descripteurs de fichiers :
        pipefd[0] : pour lire dans le pipe
        pipefd[1] : pour écrire dans le pipe

fork()

La fonction fork() permet de créer un processus enfant en dupliquant le processus courant.

    Le processus parent reçoit le PID du processus enfant.
    Le processus enfant reçoit la valeur 0 en retour de fork().
    Cela permet au parent et à l'enfant de s'exécuter en parallèle.

execve()

La fonction execve() remplace le processus courant par un nouveau programme.

    Elle est utilisée par le processus enfant après un fork() pour exécuter une commande.
    Elle prend trois arguments :
        Le chemin de la commande.
        Un tableau de chaînes de caractères représentant les arguments.
        Un tableau de chaînes de caractères représentant l'environnement.
    execve() ne retourne normalement pas, sauf en cas d'erreur.

dup2()

La fonction dup2() duplique un descripteur de fichier en remplaçant un autre.

    Par exemple, dup2(pipefd[1], STDOUT_FILENO) redirige la sortie standard vers l'extrémité d'écriture du pipe.

waitpid()

La fonction waitpid() permet au processus parent d'attendre la fin d'exécution de ses processus enfants.

    Elle suspend l'exécution du parent jusqu'à ce qu'un enfant se termine et récupère alors son code de sortie.

## Idées de Tests pour Pipex

1. **Test de base : redirection simple**
   - **Commande :**
     ```bash
     ./pipex infile "cat" "wc -l" outfile
     ```
   - **Vérification :**
     Le fichier `outfile` doit contenir le nombre de lignes du fichier `infile`.

2. **Test avec commande non valide**
   - **Commande :**
     ```bash
     ./pipex infile "invalid_command" "wc -l" outfile
     ```
   - **Vérification :**
     Le programme doit gérer l'erreur et afficher un message explicite sans planter.

3. **Test de permissions sur les fichiers**
   - **Cas :**
     Fournir un fichier d'entrée inexistant ou un fichier de sortie dans un répertoire où l'utilisateur n'a pas les droits d'écriture.
   - **Vérification :**
     Le programme doit signaler une erreur de lecture ou d'écriture.

4. **Test avec plusieurs commandes chaînées**
   - **Commande :**
     Testez avec des commandes simples comme `"grep"` et `"sort"`.
     ```bash
     ./pipex infile "grep pattern" "sort" outfile
     ```
   - **Vérification :**
     Le fichier `outfile` doit contenir les lignes triées correspondant au motif recherché dans `infile`.

5. **Test des cas limites**
   - **Cas :**
     Tester avec des fichiers volumineux ou des commandes qui produisent beaucoup de sortie.
   - **Vérification :**
     Vérifier que le programme ne présente pas de fuites de mémoire et que la redirection se fait correctement.
