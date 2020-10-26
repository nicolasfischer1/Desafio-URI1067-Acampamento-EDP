/**
/* Desafio da disciplina de EDP - tarefa avaliativa.
/* Profas Daniela {Bagatini, Saccol}.
/* Resolução do exercício 1167 - "Acampamento de férias" (do Uri Online Judge).
/* Iniciado em: 23/10/2020.
/* Última modificação em: 28/10/2020.
/* Programadores: Nicolas Fischer e Vinicius Molz.
*/

// Inclusão das bibliotecas da linguagem C.
#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura <DADO> que contêm as informações que a criança possui na ficha.
struct dados
{
    char nome[30];
    int valor;
};
typedef struct dados DADO; // Definindo um novo tipo.

// Definição da estrutura <CRIANCA> que contêm os dados da ficha e os ponteiros anterior e próximo.
// Definição da estrutura de cada nodo da lista.
struct crianca
{
    DADO dados;
    struct crianca *ant;
    struct crianca *prox;
};
typedef struct crianca CRIANCA; // Definindo um novo tipo.

// Declaração das funções que foram utilizadas no código (desenvolvidas pelo programador).
CRIANCA *entrada_dados(void);
void inclui_fim(CRIANCA **l, CRIANCA *aux);
void exclui(CRIANCA **l, CRIANCA *aux);
void vencedor(CRIANCA **l, int qtd);
void imprime_lista(CRIANCA *aux);

int main(void)
/**
/* Função principal, responsável pela execução do código (como um todo):
/* Retorno (s): número inteiro <int>.
/* Parâmetro (s): <void>, vazio.
*/
{
    //Lista deve ser global (declarada antes)
    CRIANCA *vencedores = NULL; //Contem os vencedores de todos os círculos

    while (1)
    {
        int qtd;           // Número de crianças no circulo
        scanf("%d", &qtd); // Lê o número antes do círculo ou o critério de parada
        fflush(stdin);

        if (qtd != 0)
        {
            CRIANCA *l = NULL;            // Lista temporária. A cada laço é reinisciada
            for (int j = 0; j < qtd; j++) // Executa a quantidade de vezes de "qtd"
            {
                CRIANCA *no = entrada_dados(); //Analisa os dados inseridos
                inclui_fim(&l, no);            // Inclui no fim da lista temporária
            }
            vencedor(&l, qtd);          // Deixa na lista temporário somente a criança vencedora
            inclui_fim(&vencedores, l); // Inclui a criança vencedora daquele círculo na lista de vencedores
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
/* Função que consiste em receber informações novas e armazenas em um novo espaço alocado (gera uma "criança" nova)
/* Retorno (s): ponteiro (<crianca>) que contêm o endereço de memória do novo nodo alocado.
/* Parâmetro (s): <void>, vazio.
*/
{
    CRIANCA *crianca = (CRIANCA *)malloc(sizeof(CRIANCA));       // Aloca memória
    scanf("%s %d", &crianca->dados.nome, &crianca->dados.valor); // Atribui os dados ao que foi alocado, através do ponteiro
    fflush(stdin);                                               // Limpa o buffer do teclado
    // Lista duplamente encadeada circular, manipulação dos ponteiros deste nodo (aponta para ele mesmo)
    crianca->ant = crianca;
    crianca->prox = crianca;
    return (crianca); // Retorno da função
}

void inclui_fim(CRIANCA **l, CRIANCA *aux)
/**
/* Função que inclui no fim de uma lista duplamente encadeada.
/* Retorno (s): <void>, sem retorno, modifica diretamente no endereçamento de memória.
/* Parâmetro (s): endereço do ponteiro (ponteiro para ponteiro) que marca o início da lista; e endereço de memória (ponteiro) de um nodo que deve ser colocado no final da lista.
*/
{
    if (*l == NULL) // Lista vazia (sem elementos)
    {
        *l = aux; // Faz o ponteiro que marca o início da lista receber o endereço do elemento passado como parâmetro
    }
    else // Caso a lista possua elementos
    {
        //Manipulando ponteiros de apontamento da lista e do espaço alocado (já preenchido).
        aux->prox = (*l);
        aux->ant = (*l)->ant;
        (*l)->ant->prox = aux;
        (*l)->ant = aux;
    }
}

void exclui(CRIANCA **l, CRIANCA *aux)
/**
/* Função que exclui elemento da lista.
/* Retorno (s): <void>, sem retorno, modifica diretamente no endereçamento de memória.
/* Parâmetro (s): endereço do ponteiro (ponteiro para ponteiro) que marca o início da lista; e endereço de memória (ponteiro) de um nodo que deve ser deletado da lista.
*/
{

    if (aux == (*l)) // Se for o primeiro elemento da lista a ser excluido
    {

        (*l)->prox->ant = (*l)->ant;
        (*l)->ant->prox = (*l)->prox;
        *l = (*l)->prox;
    }

    else // Caso o elemento a ser excluido não seja o primeiro
    {
        //  Manipulação dos ponteiros
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }
    free(aux); // Libera o valor contido no ponteiro aux
}

void vencedor(CRIANCA **l, int qtd)
/**
/* Função que determina o vencedor (deixa a lista somente com a criança que venceu).
/* Retorno (s): <void>, sem retorno, modifica diretamente no endereçamento de memória.
/* Parâmetro (s): endereço do ponteiro (ponteiro para ponteiro) que marca o início da lista; e a quantidade ("qtd") lida (que diz quantas crianças têm no círculo).
*/
{

    int valor = (*l)->dados.valor; // Inicializa a variável local com o valor do primeiro elemento da lista

    //Operador ternário
    //Inicializa um nodo auxiliar que irá armazenar o endereço de memória da criança a ser eliminada
    CRIANCA *eliminada = ((*l)->dados.valor % 2 == 0) ? ((*l)->ant) : ((*l)->prox); // Descobre para qual sentido a lista deve correr (horário/anti-horário) na primeira itereção.

    for (int i = 0; i < (qtd - 1); i++) // Percorre a lista até sobrar somente um elemento
    {
        for (int j = 0; j < (valor - 1); j++) // Percore a lista no sentido que depende do valor
        {
            if ((valor % 2) == 0)            // Se for par
                eliminada = eliminada->ant;  // Percorre no sentido horário
            else                             // Se for ímpar
                eliminada = eliminada->prox; //Percorre no sentido anti-horário
        }

        //Operador ternário
        CRIANCA *aux = ((eliminada->dados.valor % 2) == 0) ? (eliminada->ant) : (eliminada->prox); // Define qual elemento vai começar a ser contabilizado (a partir do valor do elemento a ser excludi, determinada o sentido da próxima iteração).
        valor = eliminada->dados.valor;                                                            // Variável recebe o valor do ponteiro eliminada
        exclui(l, eliminada);                                                                      // Utiliza função auxiliar <exclui> para eliminar o elemento contado
        eliminada = aux;                                                                           // O ponteiro auxiliar recebe o valor contabilizado antes no operador ternário (que determinou o sentido que a próxima contagem deve ser feita).
    }
}

void imprime_lista(CRIANCA *aux)
/**
/* Função que imprime todos os elementos de uma lista duplamente encadeada circular a partir do primeiro.
/* Retorno (s): <void>, sem retorno, modifica diretamente no endereçamento de memória.
/* Parâmetro (s): ponteiro (endereço de memória) que marca o início da lista.
*/
{

    CRIANCA *p = aux; // Ponteiro auxiliar que recebe o início da lista
    do                // Entra ao menos uma vez no laço (  do... while (condição)   )
    {
        printf("Vencedor(a): %s\n", p->dados.nome); // Imprime o vencedor (nome daquele elemento)
        p = p->prox;                                // Ponteiro auxiliar recebe o próximo elemento da lista

    } while (p != aux); // Enquanto não chegar novamente no primeiro elemento da lista
}
