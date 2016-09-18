#include <stdio.h>
#include <unistd.h>
/*#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>*/

/**
 * Executes the command "cat scores | grep Villanova".  In this quick-and-dirty
 * implementation the parent doesn't wait for the child to finish and
 * so the command prompt may reappear before the child terminates.
 *
 * @author Jim Glenn
 * @version 0.1 9/23/2004
 */

int main(int argc, char **argv)
{
  int pipes[2];
  int pid;

  char *cat_args[] = {"ls", "-l", NULL};
  char *grep_args[] = {"more", NULL};


  // make a pipe (fds go in pipefd[0] and pipefd[1])

  pipe(pipes);

  pid = fork();


  if(pid == 0)
    {
      // child gets here and handles "grep Villanova"

      // replace standard input with input part of pipe

      dup2(pipes[0], 0);

      // close unused hald of pipe

      close(pipes[1]);

      // execute grep

      execvp(*grep_args, grep_args);
    }
  else
    {
      // parent gets here and handles "cat scores"

      // replace standard output with output part of pipe

      dup2(pipes[1], 1);

      // close unused unput half of pipe

      close(pipes[0]);

      // execute cat

      execvp(*cat_args, cat_args);
    }
}