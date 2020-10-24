#include <stdio.h>
#include <stdlib.h>

// Defini��o da estrutura <DADO> que cont�m as informa��es que a crian�a possui na ficha.
struct dados
{
    char nome[30];
    int valor;
};
typedef struct dados DADO;  // Definindo um novo tipo.

// Defini��o da estrutura <CRIANCA> que cont�m os dados da ficha e os ponteiros anterior e pr�ximo.
// Defini��o da estrutura de cada nodo da lista.
struct crianca
{
    DADO dados;
    struct crianca *ant;
    struct crianca *prox;
};
typedef struct crianca CRIANCA; // Definindo um novo tipo.


CRIANCA *entrada_dados(void)
{
    CRIANCA *crianca = (CRIANCA *)malloc(sizeof(CRIANCA)); // Aloca mem�ria
    scanf("%s %d", &crianca->dados.nome, &crianca->dados.valor);
    fflush(stdin);
    crianca->ant = crianca;
    crianca->prox = crianca;
    return crianca;
}

void inclui_fim(CRIANCA **l, CRIANCA *aux)

{
    if (*l == NULL) // Lista vazia (sem elementos)
    {
        *l = aux; // Fun��o auxiliar <inclui_inicio>
    }
    else // Caso a lista possua elementos
    {
        //Manipulando ponteiros de apontamento da lista e do espa�o alocado (j� preenchido).
        aux->prox = (*l);
        aux->ant = (*l)->ant;
        (*l)->ant->prox = aux;
        (*l)->ant = aux;
    }
}

void exclui(CRIANCA **l, CRIANCA *aux)
{

    if (aux == (*l)) // Se for o primeiro elemento da lista a ser excluido
    {

        (*l)->prox->ant = (*l)->ant;
        (*l)->ant->prox = (*l)->prox;
        *l = (*l)->prox;
    }

    else // Caso o elemento a ser excluido n�o seja o primeiro
    {
        //  Manipula��o dos ponteiros
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }
    free(aux);
}

void vencedor(CRIANCA **l, int qtd)
{

    int valor = (*l)->dados.valor;

    CRIANCA *eliminada = ((*l)->dados.valor % 2 == 0) ? ((*l)->ant) : ((*l)->prox);
	int i;
    for (i = 0; i < (qtd - 1); i++)
    {

        if ((valor % 2) == 0)
        {
        	int j;
            for (j = 0; j < (valor - 1); j++)
                eliminada = eliminada->ant;
        }

        else
        {
        	int k;
            for (k = 0; k < (valor - 1); k++)
                eliminada = eliminada->prox;
        }

        CRIANCA *aux = ((eliminada->dados.valor % 2) == 0) ? (eliminada->ant) : (eliminada->prox);
        valor = eliminada->dados.valor;
        exclui(l, eliminada);
        eliminada = aux;
    }
}

void imprime_lista(CRIANCA *aux)
{

    CRIANCA *p = aux; // Ponteiro auxiliar para percorrer a lista
    do
    {
        printf("Vencedor(a): %s\n", p->dados.nome);
        p = p->prox;

    } while (p != aux);
}
