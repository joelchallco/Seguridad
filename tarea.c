#include <stdio.h>
#include <unistd.h>

int main()
{
/* fork a child process */
fork();
// printf("hola1\n");
/* fork another child process */
fork();
// printf("hola2\n");
/* and fork another */
fork();
printf("hola3\n");
}
