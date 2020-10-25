/**
/* Desafio da disciplina de EDP - tarefa avaliativa.
/* Profas Daniela {Bagatini, Saccol}.
/* Resolu��o do exerc�cio 1167 - "Acampamento de f�rias" (do Uri Online Judge).
/* Iniciado em: 23/10/2020.
/* �ltima modifica��o em: 28/10/2020.
/* Programadores: Nicolas Fischer e Vinicius Molz.
*/

// Inclus�o das bibliotecas da linguagem C.
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

// Declara��o das fun��es que foram utilizadas no c�digo (desenvolvidas pelo programador).
CRIANCA *entrada_dados(void);
void inclui_fim(CRIANCA **l, CRIANCA *aux);
void exclui(CRIANCA **l, CRIANCA *aux);
void vencedor(CRIANCA **l, int qtd);
void imprime_lista(CRIANCA *aux);

int main(void)
/**
/* Fun��o principal, respons�vel pela execu��o do c�digo (como um todo):
/* Retorno (s): n�mero inteiro <int>.
/* Par�metro (s): <void>, sem retorno.
*/
{
    CRIANCA *vencedores = NULL; //Lista deve ser global (declarada antes)

    while (1)
    {
        int qtd; // N�mero de crian�as no circulo
        scanf("%d", &qtd);
        fflush(stdin);

        if (qtd != 0)
        {
            CRIANCA *l = NULL; // Lista tempor�ria
            for (int j = 0; j < qtd; j++) // Percorre a lista
            {
                CRIANCA *no = entrada_dados(); //Analisa os dados inseridos
                inclui_fim(&l, no); // Inclui no fim da lista tempor�ria
            }
            vencedor(&l, qtd); // Volta para a lista principal
            inclui_fim(&vencedores, l); // Inclui no fim da lista principal
        }

        else
        {
            imprime_lista(vencedores);
            break;
        }
    }

    return 0;
}

CRIANCA *entrada_dados(void)
{
    CRIANCA *crianca = (CRIANCA *)malloc(sizeof(CRIANCA)); // Aloca mem�ria
    scanf("%s %d", &crianca->dados.nome, &crianca->dados.valor); // Atribui valores inseridos
    fflush(stdin); // Limpa o teclado
    crianca->ant = crianca; // Ponteiro aponta para o lado hor�rio
    crianca->prox = crianca; // Ponteiro aponta para o lado anti-hor�rio
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
    free(aux); // Libera o valor contido no ponteiro aux
}

void vencedor(CRIANCA **l, int qtd) //funcao para descobrir o vencedor
{

    int valor = (*l)->dados.valor; // Atribui os valores inseridos no in�cio

    CRIANCA *eliminada = ((*l)->dados.valor % 2 == 0) ? ((*l)->ant) : ((*l)->prox); // Descobre para qual sentido a lista deve correr (hor�rio/anti-hor�rio)

    for (int i = 0; i < (qtd - 1); i++) // Percorre a lista
    {

        if ((valor % 2) == 0) // Se o n�mero do primeiro a entrar na fila for PAR
        {
            for (int j = 0; j < (valor - 1); j++)
                eliminada = eliminada->ant; // Ponteiro aponta para ant
        }

        else // Se o n�mero do primeiro a entrar na fila for IMPAR
        {
            for (int k = 0; k < (valor - 1); k++)
                eliminada = eliminada->prox; // Ponteiro aponta para prox
        }

        CRIANCA *aux = ((eliminada->dados.valor % 2) == 0) ? (eliminada->ant) : (eliminada->prox); // Ponteiro aux
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
