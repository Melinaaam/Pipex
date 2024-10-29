# Pipex : |
```
./pipex	Infile "cmd1" "cmd2" Outfile

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
```
- Pipe
- fork
- dup2
- excecve
- waitpid
```

```
Pipe : int pipe (pipefd[])

creates a communication channel between two processes.

He create 2 file descriptor :
pipefd[0] : read in the pipe
pipefd[1] : write in the pipe
```

```
fork() :

creates a child processs by duplicating he current process.
The current process continu his execution and the child process  execute his execution.

The parent proess receive the PID of the child process as return from fork and the child process receive 0 as return from fork.
```

```
excecve() :

Replace the current process by a new rogram.

It use by the child process after call from fork, for executing a command.
He takes 3 av :
	- the ath of the command
	- a sring area who repreen argumets of the command
	- a string area of the environement

Excecve never return expet error
```

```
dup2() :

dulicate a file descriptor to replace it with another. Useful for redirecting standard inputs and outputs.

dup2(pipefd[1], STDOUT_FILENO)
redirects standard output to the write pipe.
```

```
waitpid() :

In computer operating systems, a process (or task) may wait for another process to complete its execution.
In most systems, a parent process can create an independently executing child process.
The parent process may then issue a wait system call, which suspends the execution of the parent process while the child executes.
When the child process terminates, it returns an exit status to the operating system, which is then returned to the waiting parent process.
The parent process then resumes execution.[1]
```

