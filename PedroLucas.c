#include <stdio.h>
#include <stdlib.h>
#include "PedroLucas.h"
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void main()
{
    lista *L;
    int cursor = 0;
    int x = 0;
    int y = 0;
    int posicaoX = 0;
    int posicaoY = 0;
    int contador = 0;
    char texto[120];
    // Necessário saber qual a linha anterior a proxima linha e o total de linhas
    int n = 0, nAnterior = 0, nProximo = 0, totalLinhas = 0;

    inicializar(&L);


    lista *aux;

    int elem;


    do
    {
        totalLinhas = 0;

        elem = _getch();

        //Para ler teclas especiais
        if(elem ==  0 || elem == 224)
            elem = _getch();

        //F1
        if(elem == 59)
        {
            F1(&L);
        }
        //F2
        else if(elem == 60)
        {
            F2(&L);
        }
        //F10
        else if(elem == 68)
        {
            F10(&L, y, x);
        }
        //F12
        else if(elem == 134)
        {
            F12(&L);
        }

        // declaro as estruturas das linhas anterior, proxima e atual - refere sempre a atual onde esta o cursor
        lista *linhaAnterior = NULL;
        lista *linhaAtual = L;
        lista *linhaProxima = NULL;
        lista *percorre = L;

        if(linhaAtual!=NULL)
        {
            int cont = 0;

            while(cont < y)
            {
                // neste if faço minha linha atual avançar e quando estou em uma posição - 1 da posição da linha linha atual, pego aquela linha como a anterior.
                // alem disto conto quantas linhas tenho ate a atual
                if(cont == (y-1))
                {
                    linhaAnterior = linhaAtual;
                }
                linhaAtual = linhaAtual->next;
                cont++;
            }

            // apenas conto o total de linhas que tem
            while(percorre != NULL)
            {
                percorre = percorre->next;
                totalLinhas = totalLinhas + 1;
            }

            // se minha linha atual tiver um next (nao for a ultima) pego o next dela como minha proxima linha
            if(linhaAtual->next != NULL)
            {
                linhaProxima = linhaAtual->next;
            }

            // Copio o texto da minha linha atual para ter mais controle e saber o que esta escrito na linha onde estou
            strcpy(texto, linhaAtual->info);
            // Pego tambem no meu vetor estatico até que posição existe texto escrito para saber onde termina a linha.
            n = linhaAtual->n;
            // pego a ultima posição da linha anterior caso haja
            if(linhaAnterior != NULL)
            {
                nAnterior = linhaAnterior->n;
            }
             // pego a ultima posição da linha proxima caso haja a linha
            if(linhaProxima != NULL)
            {
                nProximo = linhaProxima->n;
            }
        }

        // uso x e y para posicionar meu cursor na tela
        if(elem == 77)
        {
            // -->
            // se vou para direita, avanço até ser a ultima posição, apos ser a ultima posição faço y somar para passar para proxima linha e mostrar na tela
            if(texto[x] == '\n' && x == n)
            {
                y++;
                x = 0;
            }
            else if(texto[x] != '\n' && x <= n)
            {
                x++;
            }
            gotoxy(x, y);
        }
        else  if(elem == 75)
        {
            // <--
              // se vou para esquerda, avanço até ser a primeira posição, apos ser a primeira posição faço y subtrair para passar para a linha anterior e mostrar na tela
            if(x == 0)
            {
                if(y > 0)
                {
                    y--;

                    x = nAnterior;
                }
            }
            else
            {
                x--;
            }
            gotoxy(x, y);
        }
        else if(elem == 72)
        {
            // /
            // se vou para cima, avanço até ser a primeira y=0 linha, caso nao seja a primeira posição faço y subtrair para passar para linha anterior e mostrar na tela,
            // se minha posicao x desta linha que estou antes de ir para a anterior for maior que o x da anterior ele manda para o x da anterior, caso contrario o x mantem a posicao
            // caso chegar na ultima para de subir e apenas coloco o x na primeira posição da primeira linha
            if(y > 0)
            {
                y--;
            }
            if(x > nAnterior)
            {
                x = nAnterior;
            }
            gotoxy(x, y);
        }
        else  if(elem == 80)
        {
            // \/
            // se vou para baixo, avanço até ser a ultima y= totalLinhas - 1,  faço y somar para passar para proxima linha e mostrar na tela,
            // se minha posicao x desta linha que estou antes de ir para a proxima for maior que o x anterior ele manda para o x da proxima, caso contrario o x mantem a posicao
            // caso chegar na ultima para de descer e apenas coloco o x na primeira posição da linha
            if(y < totalLinhas - 1)
            {
                y++;
                if(x > nProximo)
                {
                    x = nProximo;
                }
            }

            gotoxy(x, y);
        }
        // ENTER
        else if(elem == 13)
        {
            system("cls");
            inserir(&L, &y, &x, '\n');
            exibir(&L);
        }
        else if(elem == 71)
        {
            // HOME
            x = 0;
            gotoxy(x, y);
        }
        else if(elem == 79)
        {
            // END
            x = n;
            gotoxy(x, y);
        }
        else if(elem == 73)
        {
            // PAGE UP
            if(y - 25 >= 0)
            {
                y = y - 25;
                gotoxy(x, y);
            }
            else
            {
                y = 0;
                gotoxy(x, y);
            }
            system("cls");
            exibir(&L);
        }
        else if(elem == 81)
        {
            // PAGE DOWN
            if(y + 25 <= totalLinhas - 1)
            {
                y = y - 25;
                gotoxy(x, y);
            }
            else
            {
                y = totalLinhas - 1;
                gotoxy(x, y);
            }
            system("cls");
            exibir(&L);
        }
        //INSERT
        else if(elem == 82)
        {
            elem = _getch();
            system("cls");
            insert_function(&L, &y, &x, elem);
            exibir(&L);
            gotoxy(x, y);
        }
        //DELETE
        else if(elem == 83)
        {
            system("cls");
            delete_function(&L, &y, &x);
            exibir(&L);
            gotoxy(x, y);
        }
        //BACKSPACE
        else if(elem == 8)
        {
            backspace(&L, &y, &x);
            system("cls");
            exibir(&L);
            x = x - 1;
            gotoxy(x, y);
        }
        // Caso ele nao seja nenhuma tecla especial ele escreve normalmente na tela
        else if (elem != 59 && elem != 60 && elem != 61 && elem != 62 && elem != 63 && elem != 64 && elem != -122 && elem != 27)
        {
            system("cls");
            inserir(&L, &y, &x, elem);
            exibir(&L);
            gotoxy(x, y);
        }

    }
    while(elem != 27);

    //TESTE PARA VER SE SALVO NA ESTRUTURA
    system("cls");

    exibir(&L);




}



