#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

extern char **getln();
void commandExecute(char **argv, int inputFlag, int outputFlag, char * inputFile, char *outputFile, int pipeFlag, int numOfArgs);
long int  add(char ** argv, int numOfArgs);
int arg(char ** args, int numOfArgs);
void findKillersIP();
int pigLatin(char ** args, int numOfArgs);
int pipeExecute(char ** args, int pipeFlag, int numOfArgs);
char ** adjust(int position, char ** args);

int main() {
	char **args;
	int numOfArgs;
	//These flags give the position of the  >, <, or & if found
	int inputFlag;
	int outputFlag;
	int amperFlag;
	int pipeFlag;
	char * inputFile;
	char * outputFile;

	printf("$myshell\n");

	while(1)
	{
		printf("> ");
		numOfArgs = 0;
		args = getln();
		inputFlag = -1;
		outputFlag = -1;
		amperFlag = -1;
		pipeFlag = -1;
		/*Counts the number of arguments in the command, checking for &, <, >, | flags 
		along the way. If redirection flags are set, input and output files are 
		set accordingly*/
		while(args[numOfArgs] != NULL)
		{
			if(strcmp(args[numOfArgs], "&") == 0)
			{
				amperFlag = numOfArgs;
				args = adjust(amperFlag, args);
			}
			else if(strcmp(args[numOfArgs], "<") == 0)
			{
				inputFlag = numOfArgs;
				if(args[inputFlag + 1] != NULL)
				{
					inputFile = args[inputFlag + 1];
				}
				else
				{
					printf("No input file specified\n");
					break;
				}
				args = adjust(inputFlag, args);
			}
			else if(strcmp(args[numOfArgs], ">") == 0)
			{
				outputFlag = numOfArgs;
				if(args[outputFlag + 1] != NULL)
				{
					outputFile = args[outputFlag + 1];
				}
				else
				{
					printf("No output file specified\n");
					break;
				}
				args = adjust(outputFlag, args);
			}
			else if(strcmp(args[numOfArgs], "|") == 0)
			{
				pipeFlag = numOfArgs;
			}
			numOfArgs++;				
		}
		/*If no commands are provided, continue. If defined but non-execvp commands are called,
		the appropriate functions are called. Else, call the execute function */
		if(*args == NULL)
		{
			continue;
		}
		if(strcmp(args[0], "exit") == 0)
		{
			exit(0);
		}
		else if(strcmp(args[0], "add") == 0)
		{
			add(args, numOfArgs);
		}
		else if(strcmp(args[0], "args") == 0)
		{
			arg(args, numOfArgs);
		}
		else if(strcmp(args[0], "findKillersIP") == 0)
		{
			findKillersIP();
		}
		else if(strcmp(args[0], "pig") == 0)
		{
			pigLatin(args, numOfArgs);
		}
		else
		{
			//if(numOfArgs > 1)
			commandExecute(args, inputFlag, outputFlag, inputFile, outputFile, pipeFlag, numOfArgs);
		}
	}

	return 0;
}

/*This function removes the string contained at "position" from the char ** args, and then returns args.
This function is called whenever "<" or ">" is detected. Removing these characters allow the commandExecute
to function properly when it is later called*/
char ** adjust(int position, char ** args)
{
	int i;
	for(i = position; args[i-1] != NULL; i++)
	{
		args[i] = args[i + 2];
	}

	return args;
}

/*Function which executes a command related to a video reference provided in the README*/
void findKillersIP()
{
	printf("Creating a GUI in visual basic ...\n");
	printf("Finding Killer's IP ... \n");
	printf("Segmentation fault: 11\n");	
}

/*This function is called when the user calls the "pig" command. It is a simplified version of pig latin,
where the first letter is added to the end of the word and follow by "ay"*/
int pigLatin(char ** args, int numOfArgs)
{
	int i = 1;
	int j = 1;
	if(numOfArgs == 1)
	{
		printf("0 arguments provided\n");
		return 0;
	}
	/*Cycles through all the words provided by the user.
	For each word all the letters after the first are printed, then the first letter, then "ay"*/
	while(args[i] != NULL)
	{
		j = 1;
		while(args[i][j] != '\0')
		{
			printf("%c", args[i][j]);
			j++;
		}
		printf("%c", args[i][0]);
		printf("ay ");
		i++;
	}
	printf("\n");
	return 1;
}

/*This function is called when the "args" command is entered by the user
It prints the number of arguments provided by the user and then lists them*/
int arg(char ** args, int numOfArgs)
{
	int i = 2;

	if(numOfArgs == 1)
	{
		printf("0 arguments\n");
		return 0;
	}
	printf("argc = %d, ", numOfArgs - 1);
	printf("args = %s", args[1]);
	while(args[i] != NULL)
	{
		printf(", %s", args[i]);
		i++;
	}
	printf("\n");
	return 1;
}

/*This function executes when the "add" command is called by the user.
This function adds decimal and hexadecimal values*/
long int add(char ** argv, int numOfArgs)
{
	long int ans = 0;
	int i = 1;

	if(numOfArgs == 1)
	{
		printf("Error: No values provided\n");
		return 0;
	}
	printf("%s", argv[i]);
	while(i != numOfArgs)
	{
		ans = ans + strtol(argv[i], NULL, 0);
		if(i > 1)
		{
			printf("+ %s", argv[i]);
		}
		i++;
	}
	printf(" = %ld\n", ans);
	return ans;

}

/*This function is called when a pipe is detected.
It executes the first command as input to the second*/
int pipeExecute(char ** args, int pipeFlag, int numOfArgs)
{
	int pid;
	int pipes[2];
	int i;
	int j = 0;
	int k = 0;
	numOfArgs--;
	int size = sizeof(args);

	char * beforePipe[size];
	char * afterPipe[size];
	
/*beforePipe and afterPipe are initialized so that they contains all arguments 
before and after the pipe respectively*/
	for(i = 0, j = 0; i < pipeFlag; i++)
	{
		beforePipe[j] = args[i];
		j++;
	}
	beforePipe[j] = NULL;

	for(i = pipeFlag + 1, k = 0; i <= numOfArgs; i++)
	{
		afterPipe[k] = args[i];
		k++;
	}
	afterPipe[k] = NULL;

/*Pipe is created and file descriptors are placed in the pipes[] array */
	pipe(pipes);
	pid = fork();

/*When the child process executes, dup2 is called to replace stdin with 
the beginning of the pipe. The other half of the pipe is closed. The command found
after the pipe is then executed.*/
	if(pid == 0)
	{
		dup2(pipes[0], 0);
		close(pipes[1]);
		execvp(*afterPipe, afterPipe);
	}
/*During the parent process, dup2 replaces stdout with the second half of the pipe.
The beginning of the pipe is closed, and the first command is executed*/
	else
	{
		dup2(pipes[1], 1);
		close(pipes[0]);
		execvp(*beforePipe, beforePipe);
	}


	return 0;
}

void commandExecute(char **argv, int inputFlag, int outputFlag, char * inputFile, char *outputFile, int pipeFlag, int numOfArgs)
{
    pid_t	pid = 0;
    int		forkStatus = 0;
    int		execStatus = 0; 

    pid = fork();

    if (pid == -1)
    {     //The following executes if the forking process has failed
        printf("Forking failed, now exiting\n");
        exit(1);
    }
    else if (pid == 0)
    {       
/*The following is the execution of the child process (the command).
If redirection was indicated, the appropriate I/O files are opened to replace
stdin/stdout. If a pipe was indicated, pipeExecute is called within the fork- so that
after both pipe forked processes have executed the shell is still running*/
    		if(inputFlag != -1)
    		{
    			printf("Opening file %s\n", argv[inputFlag + 1]);
    			freopen(inputFile, "r", stdin);
		    	execStatus = execvp(argv[0], argv);
    		}
    		else if(outputFlag != -1)
    		{
    			printf("Opening output file %s\n", argv[outputFlag + 1]);
    			freopen(outputFile, "w+", stdout);
		    	execStatus = execvp(argv[0], argv);
    		}
    		else if(pipeFlag != -1)
    		{
				pipeExecute(argv, pipeFlag, numOfArgs);
    		}
    		else
    		{
		    	execStatus = execvp(argv[0], argv);
    		}
	        if (execStatus == -1)
	        {     
	            printf("%s: command not found\n", *argv);
	            exit(1);
	        }
	        exit(-1);
    }
    else
    {   
    	//waits until the child process terminates 
    	while (wait(&forkStatus) != pid);      
    }
}