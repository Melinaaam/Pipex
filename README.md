# Pipex : |



## Undersatnd Unix processes in C : video



```
https://www.youtube.com/watch?v=tcYo6hipaSA&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=2
```


## Processus


Copy of a program that is running. A program is just file on the computer that does nothing until it is started. A process is the same program but once it is launched. When it is launched, the operating system gives it a unique identifier: PID (Process ID). This identifier allows the system to know which process is doing what.



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
|			|
|			|--dup2();
|			|--excecve(path,**string_av, **env);
|
|
|-------waitpid;//pid1
|-------waitpid;//pid2

```
