
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>






typedef struct sLista
{
    char info[120];
    int n;
    struct sLista *next;
} lista;


void inicializar(lista **L)
{
    *L = NULL;
}

/// ----------------------   Funcao estaticas

int vazia(lista *L)
{
    if(L->n == -1)
        return 1;
    return 0;
}

int cheia(lista *L)
{
    if(L->n == 120-1)
        return 1;
    return 0;
}

void inserir_fim(lista *L, char elem)
{
    if(cheia(L))
    {
        printf("\nErro! - Lista cheia");
        return;
    }
    L->info[L->n+1] = elem;
    L->n++;
}

void inserir_inicio(lista *L, char elem)
{
    int i;

    if(cheia(L))
    {
        printf("\nErro! - Lista cheia");
        return;
    }
    for(i = L->n; i >= 0; i--)
    {
        L->info[i+1] = L->info[i];
    }
    L->info[0] = elem;
    L->n++;
}

void inserir_posicao(lista *L, int posicao, char elem)
{
    int i;

    if(cheia(L))
    {
        printf("\nErro! - Lista cheia");
        return;
    }
    if(posicao < 0 || posicao > L->n+1)
    {
        printf("\nErro! - Elemento fora dos limites");
        return;
    }
    for(i = L->n; i >= posicao; i--)
    {
        L->info[i+1] = L->info[i];
    }
    L->info[posicao] = elem;
    L->n++;
}

void modificar(lista *L, int posicao, char elem)
{
    if(posicao < 0 || posicao > L->n+1)
    {
        printf("\nErro! - Elemento fora dos limites");
        return;
    }
    L->info[posicao] = elem;
}

int remover_inicio(lista *L)
{
    char elem;
    int i;

    if(vazia(L))
    {
        printf("\nErro! - Lista vazia");
        return -1;
    }
    elem = L->info[0];

    for(i = 0; i <= L->n; i++)
    {
        L->info[i] = L->info[i+1];
    }
    L->n--;
    return elem;
}

int remover_fim(lista *L)
{
    char elem;
    int i;

    if(vazia(L))
    {
        printf("\nErro! - Lista vazia");
        return -1;
    }
    elem = L->info[L->n];

    for(i = L->n; i <= 0; i--)
    {
        L->info[i] = L->info[i-1];
    }
    L->n--;
    return elem;
}

int remover_posicao(lista *L, int posicao)
{
    char elem;
    int i;

    if(vazia(L))
    {
        printf("\nErro! - Lista vazia");
        return -1;
    }

    if(posicao < 0 || posicao > L->n+1)
    {
        printf("\nErro! - Elemento fora dos limites");
    }
    else
    {
        elem = L->info[posicao];

        for(i = posicao; i <= L->n; i++)
        {
            L->info[i] = L->info[i+1];
        }
        L->n--;
    }
    return elem;
}

/// ----------------------   Funcao dinâmica

lista* getnode()
{
    return (lista*) malloc (sizeof(lista));
}

void freenode(lista *L)
{
    free(L);
}

int vaziaDinamica(lista *L)
{
    if(L == NULL)
        return 1;
    return 0;
}


int inserir(lista **L, int *y, int *x, char elem)
{
    lista *percorre, *auxConta;
    lista *q;

    percorre = *L;
    auxConta = *L;

    // Caso for a primeira linha

    if(percorre == NULL)
    {
        q = getnode();
        q->n = -1;

        if(q != NULL)
        {
            inserir_inicio(q, elem);
            *L = q;
        }
        *x = *x + 1;
        return -1;
    }

    int quantidade = 0;

    // Conto a quantidade de linhas

    while(auxConta != NULL)
    {
        quantidade++;
        auxConta = auxConta->next;
    }

    int cont = 0;

    // percorro as linhas ate chegar na que estou (y está na tela)
    while(cont < *y)
    {
        percorre = percorre->next;
        cont++;
    }

    // aqui só serve para linhas que estaram sendo digitadas apos receberem um \n (enter)
    // se o meu y for menor q a quantidade, quer dizer que não estou na ultima linha
    // então apago o \n daquela linha que estou, escrevo o novo caracter e depois coloco a frente um outro \n
    if(*y < quantidade - 1)
    {
        // aqui é para caso eu esteja digitando no final da linha que movi o ponteiro para digitar
        if(*x == percorre->n && percorre->info[percorre->n] == '\n')
        {
            remover_fim(percorre);
            if(percorre->n != 118)
            {
                inserir_fim(percorre, elem);
                *x = percorre->n + 1;
                inserir_fim(percorre, '\n');
                return;
            }
        }
        else if(percorre->n <= 118)
        {
            //aqui é se estou digitando no meio da linha
            inserir_posicao(percorre, *x, elem);
            *x = *x + 1;
            return;
        }
    }

    //se tiver na ultima posição de um linha coloco um \n e crio um novo nó inserindo no inicio dele a letra digitada. aumento o x para dizer que a
    // posicao do caracter esta aumentando
    if(percorre->n == 120 - 2)
    {
        inserir_fim(percorre, '\n');
        q = getnode();
        q->n = -1;
        *y = *y + 1;

        if(*y < quantidade - 1)
        {
            q->next = percorre->next;
        }
        if(q != NULL)
        {
            inserir_inicio(q, elem);
            percorre->next = q;
        }

        *x = 0;


        return;
    }

    // se for um \n que foi digitado, apenas crio um novo nó e aumento a minha linha y
    if(elem == '\n')
    {
        inserir_fim(percorre, elem);

        q = getnode();
        q->n = -1;
        *y = *y + 1;

        if(q != NULL)
        {
            percorre->next = q;
        }

        *x = 0;
    }
    else
    {
        // se nao for um \n ele apenas continua digitando na mesma linha aumentando o seu x
        *x = *x + 1;
        inserir_fim(percorre, elem);
    }


    return;
}

void remover(lista **L, int y, int x)
{
    lista *percorre = *L;

    int cont = 0;
    // acho a linha em que estou pelo meu y
    while(cont < y)
    {
        percorre = percorre->next;
    }

    // se meu x for 0, estou na primeira linha entao apago no inicio
    if((x - 1) == 0)
    {
        remover_inicio(percorre);
    }
    else if((x - 1) == 119)
    {
        // se estiver no fim, apago o \n e apago a letra anterior ao \n
        remover_fim(percorre);
        remover_fim(percorre);
    }
    else
    {
        // caso eu apague no meio de um texto
        remover_posicao(percorre, x);
    }


}


/// ----------------------   ATALHOS

void F1(lista **L)
{
    int verificacao;
    char caracter;

    FILE *arquivo;

    arquivo = fopen("PedroLucas_ajuda.txt", "r");

    if(arquivo == NULL)
    {
        exit(1);
    }
    system("cls");

    while((caracter = fgetc(arquivo)) != EOF)
    {
        printf("%c", caracter);
    }

    fclose(arquivo);

    verificacao = _getch();

    if(verificacao == 27)
    {
        system("cls");
        exibir(L);
    }
}

void F2(lista **L)
{
    FILE *arquivo;
    lista *percorre = *L;

    arquivo = fopen("PedroLucas.txt", "w");


    if(arquivo == NULL)
    {
        system("cls");
        printf("não foi possivel abrir o arquivo");
    }
    else
    {

        while(percorre != NULL)
        {
            for(int i = 0; i < 120 && i < (percorre->n + 1); i++)
            {
                fputc(percorre->info[i], arquivo);
            }
            percorre = percorre->next;
        }
    }

    fclose(arquivo);
}

void F10(lista **L, int y, int x)
{
    FILE *arquivo;
    char caracter;
    lista *aux = *L;

    system("cls");
    arquivo = fopen("PedroLucasPreDefinido.txt", "r");

    if(arquivo == NULL)
    {
        system("cls");
        printf("não foi possivel abrir o arquivo");
    }
    else
    {
        *L = NULL;
        freenode(aux);
        while((caracter = fgetc(arquivo)) != EOF)
        {
            inserir(&(*L), &y, &x, caracter);
        }
    }
    fclose(arquivo);
    exibir(&(*L));

}

void F12(lista **L)
{
    int verificacao;

    system("cls");

    printf("=============================================\n");
    printf("            DADOS DO ALUNO\n");
    printf("=============================================\n\n");

    printf("  Prontuario: PE3008819\n");
    printf("  Nome: Pedro Lucas Calvo Baschoni\n");
    printf("  Curso: Ciencias da Computacao\n");
    printf("  Ano de ingresso: 2021\n\n");

    printf("=============================================\n");
    printf("  Aperte ESC para sair...\n");
    printf("=============================================\n");

    verificacao = _getch();

    if(verificacao == 27)
    {
        system("cls");
        exibir(L);
    }

}

void insert_function(lista **L, int *y, int *x, char elem)
{
    lista *percorre;
    lista *q;

    percorre = *L;
    //se nao tiver linha e quiser usar insert nao funciona
    if(percorre == NULL)
    {
        return;
    }

    int cont = 0;
    // acho minha linha
    while(cont < *y)
    {
        percorre = percorre->next;
        cont++;
    }

    //substituo na posicao x o elemento
    percorre->info[*x] = elem;

    return;
}


void delete_function(lista **L, int *y, int *x)
{
    lista *percorre;
    lista *q;

    percorre = *L;

    if(percorre == NULL)
    {
        return;
    }

    int cont = 0;
    //acho minha linha
    while(cont < *y)
    {
        percorre = percorre->next;
        cont++;
    }
    //removo a posicao x q o elemento esta
    remover_posicao(percorre, *x);

    return;
}

void backspace(lista **L, int *y, int *x)
{
    lista *percorre;
    lista *anterior = NULL;
    lista *q;

    percorre = *L;

    //posicao anterior do y
    int ant = 0;

    if(percorre == NULL)
    {
        return;
    }

    int cont = 0;

    if(*y > 0)
    {
        ant = *y - 1;
    }

    //pego minha linha atual y e a anterior para subir a linha quando apago
    while(cont < *y)
    {
        if(*y > 0 && ant == *y)
        {
            anterior = percorre;
        }
        percorre = percorre->next;
        cont++;
    }

    //se nao for estiver vazia eu apago a posicao x em que estou
    if(percorre->n != -1)
    {
        remover_posicao(percorre, *x);
    }

    else
    {
        // se for percorrer dou um free na linha, subtraio meu y e coloco q meu x fica na posicao n da linha anterior
        freenode(percorre);
        *x = anterior->n;
        anterior->next = NULL;
        *y = *y - 1;
    }



    return;
}

void exibir(lista **L)
{
    lista *percorre;
    percorre = *L;



    while(percorre != NULL)
    {
        for(int i = 0; i < 120 && i < (percorre->n + 1); i++)
        {
            printf("%c", percorre->info[i]);
        }
        percorre = percorre->next;
    }
}


