#include <stdlib.h>
#include "chess.h"
#include <iostream>
#include <time.h>

//rbbrbbrrb

using namespace std;

bool revision(string);
void llenarCadena(string *, int);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int tam = 1+rand()%10;
    Jugador jugador, jugador2;
    int mode = argv[1][0] - 48;
    int player = argv[2][0] - 48;
    int cant = argv[3][0] - 48;
    string cadena,cadena2;
    if (argc == 5 && mode == 1)
    {
        cadena = argv[4];
    }
    else
    {
        llenarCadena(&cadena, tam);
    }
    if (player == 1)
    {
        jugador.initJugador(1, 16, mode, cadena);
    }
    else
    {
        jugador.initJugador(4, 13, mode, cadena);
    }
    Chess chess;
    if (cant == 1)
    {
        chess.initChess(jugador);
        cout << cadena << endl;
    }
    else
    {
        cout << cadena << endl;
        jugador.initJugador(1, 16, mode, cadena);
        llenarCadena(&cadena2, tam);
        cout << cadena2 << endl;
        jugador2.initJugador(4, 13, mode, cadena2);
        chess.initChess(jugador);
        chess.initChess(jugador2);
    }

    return 0;
}

bool revision(string cadena)
{
    for (char c : cadena)
    {
        if (c != 'b' && c != 'r')
        {
            return false;
        }
    }
    return true;
}

void llenarCadena(string *cadena, int tam)
{
    char len[] = {'r', 'b'};
    for (int i = 0; i < tam; i++)
    {
        *cadena += len[rand() % 2];
    }
}