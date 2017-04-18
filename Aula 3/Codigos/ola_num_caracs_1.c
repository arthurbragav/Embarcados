#include <stdio.h>
#include "num_caracs.h"

int main(int argc, char **argv)
{
int contador=0;

for (contador=0;contador<argc;contador++)
{
 printf ("Argumento: %s / Numero de caracteres: %d\n", argv[contador],Num_Caracs(argv[contador]));
}
 
 return 0;
}