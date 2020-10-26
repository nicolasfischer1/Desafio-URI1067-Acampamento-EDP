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
typedef struct dados DADO; // Definindo um novo tipo.

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
/* Par�metro (s): <void>, vazio.
*/
{
    //Lista deve ser global (declarada antes)
    CRIANCA *vencedores = NULL; //Contem os vencedores de todos os c�rculos

    while (1)
    {
        int qtd;           // N�mero de crian�as no circulo
        scanf("%d", &qtd); // L� o n�mero antes do c�rculo ou o crit�rio de parada
        fflush(stdin);

        if (qtd != 0)
        {
            CRIANCA *l = NULL;            // Lista tempor�ria. A cada la�o � reinisciada
            for (int j = 0; j < qtd; j++) // Executa a quantidade de vezes de "qtd"
            {
                CRIANCA *no = entrada_dados(); //Analisa os dados inseridos
                inclui_fim(&l, no);            // Inclui no fim da lista tempor�ria
            }
            vencedor(&l, qtd);          // Deixa na lista tempor�rio somente a crian�a vencedora
            inclui_fim(&vencedores, l); // Inclui a crian�a vencedora daquele c�rculo na lista de vencedores
        }

        else // Caso seja digitado 0
        {
            imprime_lista(vencedores); // Imprime a lista de vencedores
            break;                     // Pula fora do while
        }
    }

    return 0;
}

CRIANCA *entrada_dados(void)
/**
/* Fun��o que consiste em receber informa��es novas e armazenas em um novo espa�o alocado (gera uma "crian�a" nova)
/* Retorno (s): ponteiro (<crianca>) que cont�m o endere�o de mem�ria do novo nodo alocado.
/* Par�metro (s): <void>, vazio.
*/
{
    CRIANCA *crianca = (CRIANCA *)malloc(sizeof(CRIANCA));       // Aloca mem�ria
    scanf("%s %d", &crianca->dados.nome, &crianca->dados.valor); // Atribui os dados ao que foi alocado, atrav�s do ponteiro
    fflush(stdin);                                               // Limpa o buffer do teclado
    // Lista duplamente encadeada circular, manipula��o dos ponteiros deste nodo (aponta para ele mesmo)
    crianca->ant = crianca;
    crianca->prox = crianca;
    return (crianca); // Retorno da fun��o
}

void inclui_fim(CRIANCA **l, CRIANCA *aux)
/**
/* Fun��o que inclui no fim de uma lista duplamente encadeada.
/* Retorno (s): <void>, sem retorno, modifica diretamente no endere�amento de mem�ria.
/* Par�metro (s): endere�o do ponteiro (ponteiro para ponteiro) que marca o in�cio da lista; e endere�o de mem�ria (ponteiro) de um nodo que deve ser colocado no final da lista.
*/
{
    if (*l == NULL) // Lista vazia (sem elementos)
    {
        *l = aux; // Faz o ponteiro que marca o in�cio da lista receber o endere�o do elemento passado como par�metro
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
/**
/* Fun��o que exclui elemento da lista.
/* Retorno (s): <void>, sem retorno, modifica diretamente no endere�amento de mem�ria.
/* Par�metro (s): endere�o do ponteiro (ponteiro para ponteiro) que marca o in�cio da lista; e endere�o de mem�ria (ponteiro) de um nodo que deve ser deletado da lista.
*/
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

void vencedor(CRIANCA **l, int qtd)
/**
/* Fun��o que determina o vencedor (deixa a lista somente com a crian�a que venceu).
/* Retorno (s): <void>, sem retorno, modifica diretamente no endere�amento de mem�ria.
/* Par�metro (s): endere�o do ponteiro (ponteiro para ponteiro) que marca o in�cio da lista; e a quantidade ("qtd") lida (que diz quantas crian�as t�m no c�rculo).
*/
{

    int valor = (*l)->dados.valor; // Inicializa a vari�vel local com o valor do primeiro elemento da lista

    //Operador tern�rio
    //Inicializa um nodo auxiliar que ir� armazenar o endere�o de mem�ria da crian�a a ser eliminada
    CRIANCA *eliminada = ((*l)->dados.valor % 2 == 0) ? ((*l)->ant) : ((*l)->prox); // Descobre para qual sentido a lista deve correr (hor�rio/anti-hor�rio) na primeira itere��o.

    for (int i = 0; i < (qtd - 1); i++) // Percorre a lista at� sobrar somente um elemento
    {
        for (int j = 0; j < (valor - 1); j++) // Percore a lista no sentido que depende do valor
        {
            if ((valor % 2) == 0)            // Se for par
                eliminada = eliminada->ant;  // Percorre no sentido hor�rio
            else                             // Se for �mpar
                eliminada = eliminada->prox; //Percorre no sentido anti-hor�rio
        }

        //Operador tern�rio
        CRIANCA *aux = ((eliminada->dados.valor % 2) == 0) ? (eliminada->ant) : (eliminada->prox); // Define qual elemento vai come�ar a ser contabilizado (a partir do valor do elemento a ser excludi, determinada o sentido da pr�xima itera��o).
        valor = eliminada->dados.valor;                                                            // Vari�vel recebe o valor do ponteiro eliminada
        exclui(l, eliminada);                                                                      // Utiliza fun��o auxiliar <exclui> para eliminar o elemento contado
        eliminada = aux;                                                                           // O ponteiro auxiliar recebe o valor contabilizado antes no operador tern�rio (que determinou o sentido que a pr�xima contagem deve ser feita).
    }
}

void imprime_lista(CRIANCA *aux)
/**
/* Fun��o que imprime todos os elementos de uma lista duplamente encadeada circular a partir do primeiro.
/* Retorno (s): <void>, sem retorno, modifica diretamente no endere�amento de mem�ria.
/* Par�metro (s): ponteiro (endere�o de mem�ria) que marca o in�cio da lista.
*/
{

    CRIANCA *p = aux; // Ponteiro auxiliar que recebe o in�cio da lista
    do                // Entra ao menos uma vez no la�o (  do... while (condi��o)   )
    {
        printf("Vencedor(a): %s\n", p->dados.nome); // Imprime o vencedor (nome daquele elemento)
        p = p->prox;                                // Ponteiro auxiliar recebe o pr�ximo elemento da lista

    } while (p != aux); // Enquanto n�o chegar novamente no primeiro elemento da lista
}
