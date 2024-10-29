# Pipex : |



## Undersatnd Unix processes in C : video



```
https://www.youtube.com/watch?v=tcYo6hipaSA&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=2
```


## Processus

By default :
```
STDIN------>cmd------>STDOUT
0			1
```

With a pipe  :

```
./pipex		Infile------->cmd1--PIPE--->cmd2------->Outfile
STD				0			1		0				1
				|			|		|				|
			open(infile)	|		fd[0](read)		open(outfile)
							fd[1](write)
```

Copy of a program that is running. A program is just file on the computer that does nothing until it is started. A process is the same program but once it is launched. When it is launched, the operating system gives it a unique identifier: PID (Process ID). This identifier allows the system to know which process is doing what.


