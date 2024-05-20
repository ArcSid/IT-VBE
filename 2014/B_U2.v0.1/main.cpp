#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Savivaldybe
{
    string miestasKuriamPriklauso;
    int mokykluKiekis;
};

struct Miestas
{
    string pavadinimas;
    vector<int> mokykuKiekiaiSavivaldybese;
    int didziausiasMokykluKiekisSavivaldybeje;
};

int rastiMaximuma(vector<int> masyvas)
{
    int max_i = 0;
    for (int i = 0; i < masyvas.size(); i++)
    {
        if (masyvas[max_i] < masyvas[i])
        {
            max_i = i;
        }
    }
    return masyvas[max_i];
}

void skaitytiIsFailo(int &savivaldybiuKiekis, Savivaldybe savivaldybes[])
{
    ifstream data("U2.txt");
    data >> savivaldybiuKiekis;

    string laikinasSakinys;

    for (int i = 0; i < savivaldybiuKiekis; i++)
    {
        data >> laikinasSakinys;
        data >> savivaldybes[i].mokykluKiekis;
        data >> savivaldybes[i].miestasKuriamPriklauso;
    }
    data.close();
}

void sudetiSavivaldybesIMiestus(int savivaldybiuKiekis, Savivaldybe savivaldybes[], int &miestuKiekis, Miestas miestai[])
{
    for (int i = 0; i < savivaldybiuKiekis; i++)
    {
        bool naujasMiestas = true;

        for (int j = 0; j < miestuKiekis; j++)
        {
            if (miestai[j].pavadinimas == savivaldybes[i].miestasKuriamPriklauso)
            {
                naujasMiestas = false;
                miestai[j].mokykuKiekiaiSavivaldybese.push_back(savivaldybes[i].mokykluKiekis);
                break;
            }
        }
        if (!naujasMiestas)
        {
            continue;
        }

        miestai[miestuKiekis].pavadinimas = savivaldybes[i].miestasKuriamPriklauso;
        miestai[miestuKiekis].mokykuKiekiaiSavivaldybese.push_back(savivaldybes[i].mokykluKiekis);
        miestuKiekis++;
    }
}

void surikiuotiMiestus(int miestuKiekis, Miestas miestai[])
{
    for (int i = 0; i < miestuKiekis; i++)
    {
        for (int j = 0; j < miestuKiekis - 1 - i; j++)
        {
            if (miestai[j].didziausiasMokykluKiekisSavivaldybeje < miestai[j + 1].didziausiasMokykluKiekisSavivaldybeje)
            {
                swap(miestai[j], miestai[j + 1]);
            }
        }
    }
}

void rez(int miestuKiekis, Miestas miestai[])
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < miestuKiekis; i++)
    {
        rez << left << setw(14) << miestai[i].pavadinimas << miestai[i].mokykuKiekiaiSavivaldybese.size() << " " << miestai[i].didziausiasMokykluKiekisSavivaldybeje << endl;
    }
    rez.close();
}

int main()
{
    int savivaldybiuKiekis;
    Savivaldybe savivaldybes[60];
    skaitytiIsFailo(savivaldybiuKiekis, savivaldybes);

    int miestuKiekis = 0;
    Miestas miestai[60];
    sudetiSavivaldybesIMiestus(savivaldybiuKiekis, savivaldybes, miestuKiekis, miestai);

    for (int i = 0; i < miestuKiekis; i++)
    {
        miestai[i].didziausiasMokykluKiekisSavivaldybeje = rastiMaximuma(miestai[i].mokykuKiekiaiSavivaldybese);
    }

    surikiuotiMiestus(miestuKiekis, miestai);
    rez(miestuKiekis, miestai);

    return 0;
}
