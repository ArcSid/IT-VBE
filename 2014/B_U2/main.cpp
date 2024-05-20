#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Apskritis
{
    string pavadinimas;
    int miestuKiekis = 0;
    int maxMokykluKiekis;
};

void skaitytiIsFailo(int &apskriciuKiekis, Apskritis apskritys[])
{
    ifstream data("U2.txt");
    int miestuKiekis;
    int mokykluKiekisMieste;
    string apskritiesPavadinimas;
    data >> miestuKiekis;

    string miestoPavadinimas;

    for (int i = 0; i < miestuKiekis; i++)
    {
        // savivaldybes == miesto pavadinimas
        data >> miestoPavadinimas;

        data >> mokykluKiekisMieste;
        data >> apskritiesPavadinimas;
        bool naujaApskritis = true;

        for (int j = 0; j < apskriciuKiekis; j++)
        {
            if (apskritys[j].pavadinimas == apskritiesPavadinimas)
            {
                apskritys[j].miestuKiekis++;
                if (apskritys[j].maxMokykluKiekis < mokykluKiekisMieste)
                {
                    apskritys[j].maxMokykluKiekis = mokykluKiekisMieste;
                }
                naujaApskritis = false;
                break;
            }
        }
        if (naujaApskritis)
        {
            apskritys[apskriciuKiekis].pavadinimas = apskritiesPavadinimas;
            apskritys[apskriciuKiekis].maxMokykluKiekis = mokykluKiekisMieste;
            apskritys[apskriciuKiekis].miestuKiekis++;
            apskriciuKiekis++;
        }
    }
    data.close();
}

void surikiuotiApskritis(int apskriciuKiekis, Apskritis apskritys[])
{
    for (int i = 0; i < apskriciuKiekis; i++)
    {
        for (int j = 0; j < apskriciuKiekis - 1 - i; j++)
        {
            if (apskritys[j].maxMokykluKiekis < apskritys[j + 1].maxMokykluKiekis)
            {
                swap(apskritys[j], apskritys[j + 1]);
            }
            else if (apskritys[j].maxMokykluKiekis == apskritys[j + 1].maxMokykluKiekis && apskritys[j].pavadinimas > apskritys[j + 1].pavadinimas)
            {
                swap(apskritys[j], apskritys[j + 1]);
            }
        }
    }
}

void rez(int apskriciuKiekis, Apskritis apskritys[])
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < apskriciuKiekis; i++)
    {
        rez << left << setw(14) << apskritys[i].pavadinimas << apskritys[i].miestuKiekis << " " << apskritys[i].maxMokykluKiekis << endl;
    }
    rez.close();
}

int main()
{
    int apskriciuKiekis = 0;
    Apskritis apskritys[60];
    skaitytiIsFailo(apskriciuKiekis, apskritys);
    surikiuotiApskritis(apskriciuKiekis, apskritys);
    rez(apskriciuKiekis, apskritys);
}