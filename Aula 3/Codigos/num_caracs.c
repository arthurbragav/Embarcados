#include <stdio.h>
#include "num_caracs.h"
int Num_Caracs(char *string)
{
int contador=0;
while(string[contador]!='\0')
contador++;

return contador;

}