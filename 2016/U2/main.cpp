#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Pratimas
{
    string pavadinimas;
    int kartai = 0;
};

void skaitymas(vector<Pratimas> &pratimai)
{

    ifstream data("U2.txt");
    int duomenu_eiluciu_sk = 0;
    data >> duomenu_eiluciu_sk;

    int atlikimu_kiekis;

    for (int i = 0; i < duomenu_eiluciu_sk; i++)
    {

        string pavadinimas;
        Pratimas laikinas_pratimas;
        char ch[21];

        data.read(ch, 1);
        data.read(ch, 20);

        pavadinimas = ch;
        data >> atlikimu_kiekis;

        int egzistuojacio_pratimo_indeksas = -1;

        for (int j = 0; j < pratimai.size(); j++)
        {
            if (pavadinimas == pratimai[j].pavadinimas)
            {
                egzistuojacio_pratimo_indeksas = j;
                break;
            }
        }

        if (egzistuojacio_pratimo_indeksas != -1)
        {
            pratimai[egzistuojacio_pratimo_indeksas].kartai += atlikimu_kiekis;
            continue;
        }

        laikinas_pratimas.pavadinimas = pavadinimas;
        laikinas_pratimas.kartai += atlikimu_kiekis;
        pratimai.push_back(laikinas_pratimas);
    }
}

void sort(vector<Pratimas> &pratimai)
{
    for (int i = 0; i < pratimai.size(); i++)
    {
        for (int j = 0; j < pratimai.size() - 1 - i; j++)
        {
            if (pratimai[j].kartai < pratimai[j + 1].kartai)
            {
                swap(pratimai[j], pratimai[j + 1]);
            }
        }
    }
}

void rez(vector<Pratimas> pratimai)
{

    ofstream rez("U2rez.txt");

    for (int i = 0; i < pratimai.size(); i++)
    {
        rez << pratimai[i].pavadinimas << pratimai[i].kartai << endl;
    }
}

int main()
{
    vector<Pratimas> pratimai;
    skaitymas(pratimai);
    sort(pratimai);
    rez(pratimai);
    return 0;
}