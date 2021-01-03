#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <list>
#include "square.h"
#include "Player.h"
using namespace std;

#define ROWS_NUM 4
typedef list<int> lista;

class Chess
{
public:
    Square squareBoard[ROWS_NUM][ROWS_NUM];
    Jugador jugador;
    ofstream all, wins;
    map<int, char> colorCell;
    map<int, lista> movesToR;
    map<int, lista> movesToB;

    void initChess(Jugador);
    void crearTablero();
    void abrirArchivos();
    void cerrarArchivos();
    void inicio();
    void printCaminos(int, lista, int, lista);
    lista getNextMoves(int, int);
    void fillWays();
};

void Chess::initChess(Jugador p)
{
    jugador = p;
    crearTablero();
    abrirArchivos();
    crearTablero();
    fillWays();
    inicio();
    cerrarArchivos();
}

void Chess::abrirArchivos()
{
    wins.open(jugador.archivo_ganadoras);
    all.open(jugador.archivo_todas);
}

void Chess::cerrarArchivos()
{
    wins.close();
    all.close();
}

void Chess::crearTablero()
{
    Square square;
    int counter = 1;
    char color;
    //pendiente de revision de rangos e indices
    for (int i = 0; i < ROWS_NUM; i++)
    {
        for (int j = 0; j < ROWS_NUM; j++)
        {
            if ((counter + i) % 2 == 1)
            {
                color = 'r';
            }
            else
            {
                color = 'b';
            }
            colorCell[counter] = color;
            square.setNumber(counter);
            square.setColor(color);
            squareBoard[i][j] = square;
            counter++;
        }
    }
}

void Chess::inicio()
{
    int q0 = jugador.posicion;
    list<int> temp;
    printCaminos(q0, getNextMoves(q0, 0), 1, temp);
}

void Chess::printCaminos(int actual, list<int> moves, int cont, list<int> camino)
{
    camino.push_back(actual);
    if (cont == jugador.cadena.length())
    {
        if (actual == jugador.pos_ganadora)
        {
            bool primer = true;
            for (int it : camino)
            {
                if (primer)
                {
                    wins << it;
                    all << it;
                    primer = false;
                }
                else
                {
                    wins << " " << it;
                    all << " " << it;
                }
            }
            wins << endl;
            all << endl;
            return;
        }
        else
        {
            bool primer = true;
            for (int it : camino)
            {
                if (primer)
                {
                    all << it;
                    primer = false;
                }
                else
                {
                    all << " " << it;
                }
            }
            all << endl;
            return;
        }
    }
    else
    {
        for (int it : camino)
        {
            printCaminos(it, getNextMoves(it, cont), cont + 1, camino);
        }
    }
}
void Chess::fillWays()
{
    //caminos de R first llave, second valor
    for (map<int, char>::iterator it = colorCell.begin(); it != colorCell.end(); ++it)
    {
        list<int> m, h;
        //diagonales

        if (it->first - 5 > 0)
        {
            m.push_back(it->first - 5);
        }
        if (it->first + 5 <= 16)
        {
            m.push_back(it->first + 5);
        }

        if (it->first - 3 > 0)
        {
            m.push_back(it->first - 3);
        }
        if (it->first + 3 <= 16)
        {
            m.push_back(it->first + 3);
        }
        //ortogonales

        if (it->first - 1 > 0)
        {
            h.push_back(it->first - 1);
        }
        if (it->first + 1 <= 16)
        {
            h.push_back(it->first + 1);
        }

        if (it->first - 4 > 0)
        {
            h.push_back(it->first - 4);
        }
        if (it->first + 4 <= 16)
        {
            h.push_back(it->first + 4);
        }
        if (it->second == 'r')
        {
            movesToB[it->first] = m;
            movesToR[it->first] = h;
        }
        else
        {
            movesToB[it->first] = h;
            movesToR[it->first] = m;
        }
    }
    cout << "movimientos para B" << endl;
    for (map<int, lista>::iterator it = movesToB.begin(); it != movesToB.end(); ++it)
    {
        cout << it->first << " : ";
        for (int x : it->second)
            cout << x << " ";
        cout << endl;
    }
    cout << "Movimientos para R" << endl;
    for (map<int, lista>::iterator it = movesToR.begin(); it != movesToR.end(); ++it)
    {
        cout << it->first << " : ";
        for (int x : it->second)
            cout << x << " ";
        cout << endl;
    }
}
list<int> Chess::getNextMoves(int casilla, int letra)
{
    if (jugador.cadena[letra] == 'r')
    {
        return movesToR[casilla];
    }
    else
    {
        return movesToB[casilla];
    }
}