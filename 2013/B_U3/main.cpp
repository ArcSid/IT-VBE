#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Zvejys
{
    string vardas;
    int karosai = 0;
    int karpes = 0;
    int kuojos = 0;

    int suma = 0;
};

void skaitytiDuomenis(int &zvejuKiekis, Zvejys zvejai[])
{
    ifstream data("U3.txt");
    data >> zvejuKiekis;
    for (int i = 0; i < zvejuKiekis; i++)
    {
        Zvejys laikinasisZvejys;
        char ch[11] = {0};
        data.ignore();
        data.read(ch, 10);

        laikinasisZvejys.vardas = ch;
        int dienuKiekis;
        data >> dienuKiekis;

        for (int j = 0; j < dienuKiekis; j++)
        {
            int zuviesKiekis;
            data >> zuviesKiekis;
            laikinasisZvejys.karosai += zuviesKiekis;
            data >> zuviesKiekis;
            laikinasisZvejys.karpes += zuviesKiekis;
            data >> zuviesKiekis;
            laikinasisZvejys.kuojos += zuviesKiekis;
        }
        
        laikinasisZvejys.suma = laikinasisZvejys.karosai + laikinasisZvejys.karpes + laikinasisZvejys.kuojos;
        zvejai[i] = laikinasisZvejys;
    }
    data.close();
}

Zvejys geriausiasZvejys(int zvejuKiekis, Zvejys zvejai[])
{
    int max_i = 0;
    for (int i = 0; i < zvejuKiekis; i++)
    {
        if (zvejai[i].suma > zvejai[max_i].suma)
        {
            max_i = i;
        }
    }
    return zvejai[max_i];
}

void rez(int zvejuKiekis, Zvejys zvejai[], Zvejys geriausiasZv)
{
    ofstream rez("U3rez.txt");
    for (int i = 0; i < zvejuKiekis; i++)
    {
        rez << zvejai[i].vardas << " " << setw(5) << zvejai[i].karosai << " " << setw(5) << zvejai[i].karpes << " " << setw(5) << zvejai[i].kuojos << endl;
    }
    rez << geriausiasZv.vardas << " " << setw(5) << geriausiasZv.suma << endl;
    rez.close();
}

int main()
{
    int zvejuKiekis;
    Zvejys zvejai[100];
    skaitytiDuomenis(zvejuKiekis, zvejai);

    Zvejys geriausiasZv = geriausiasZvejys(zvejuKiekis, zvejai);
    rez(zvejuKiekis, zvejai, geriausiasZv);
    return 0;
}