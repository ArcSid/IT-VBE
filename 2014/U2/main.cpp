#include <iostream>
#include <fstream>
using namespace std;

struct Koordinates
{
    int x;
    int y;
};

struct Komandu_seka
{
    int ilgis;
    int komandos[30];
    int kiek_praejo;
};

void skaitymas(int &seku_kiekis, Koordinates &pradzia, Koordinates &pabaiga, Komandu_seka komandu_sekos[])
{
    ifstream data("U2.txt");
    data >> pradzia.x;
    data >> pradzia.y;
    data >> pabaiga.x;
    data >> pabaiga.y;
    data >> seku_kiekis;
    for (int i = 0; i < seku_kiekis; i++)
    {
        data >> komandu_sekos[i].ilgis;
        for (int j = 0; j < komandu_sekos[i].ilgis; j++)
        {
            data >> komandu_sekos[i].komandos[j];
        }
    }
}

int execute_command(Koordinates pradzia, Koordinates pabaiga, Komandu_seka komandu_seka)
{
    for (int i = 0; i < komandu_seka.ilgis; i++)
    {
        if (komandu_seka.komandos[i] == 1)
        {
            pradzia.y += 1;
        }
        if (komandu_seka.komandos[i] == 3)
        {
            pradzia.y -= 1;
        }
        if (komandu_seka.komandos[i] == 2)
        {
            pradzia.x += 1;
        }
        if (komandu_seka.komandos[i] == 4)
        {
            pradzia.x -= 1;
        }
        if (pradzia.x == pabaiga.x && pradzia.y == pabaiga.y)
        {
            return i + 1;
        }
    }
    return -1;
}

void rez(int seku_kiekis, Komandu_seka komandu_sekos[])
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < seku_kiekis; i++)
    {
        if (komandu_sekos[i].kiek_praejo == -1)
        {
            rez << "sekos pabaiga       ";
            for (int j = 0; j < komandu_sekos[i].ilgis; j++)
            {
                rez << komandu_sekos[i].komandos[j] << " ";
            }
            rez << komandu_sekos[i].ilgis << endl;
            continue;
        }
        rez << "pasiektas tikslas   ";
        for (int j = 0; j < komandu_sekos[i].kiek_praejo; j++)
        {
            rez << komandu_sekos[i].komandos[j] << " ";
        }
        rez << komandu_sekos[i].kiek_praejo << endl;
    }
}

int main()
{
    Koordinates pradzia;
    Koordinates pabaiga;
    Komandu_seka komandu_sekos[10];
    int seku_kiekis;
    skaitymas(seku_kiekis, pradzia, pabaiga, komandu_sekos);
    for (int i = 0; i < seku_kiekis; i++)
    {
        komandu_sekos[i].kiek_praejo = execute_command(pradzia, pabaiga, komandu_sekos[i]);
    }
    rez(seku_kiekis, komandu_sekos);
}