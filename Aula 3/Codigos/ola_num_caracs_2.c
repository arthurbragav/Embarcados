#include <stdio.h>
#include "num_caracs.h"

int main(int argc, char **argv)
{
int contador=0;
int caracs=0;

for (contador=0;contador<argc;contador++)
{
 caracs = caracs + Num_Caracs(argv[contador]);
}
printf ("Total de caracteres de entrada: %d\n",caracs);
 return 0;
}