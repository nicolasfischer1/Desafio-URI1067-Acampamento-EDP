#include <stdio.h>
#include <stdlib.h>
#include<string.h>


void main ()
{
    char nome [30];
    int numero;
    scanf("%s %d", &nome, &numero);
    fflush(stdin);
    printf("--------------------------\n");
    printf("%s\n", nome);
    printf("%d\n", numero);
}