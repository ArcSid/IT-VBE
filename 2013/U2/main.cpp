#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Apskritis
{
    string pavadinimas;

    vector<int> miestu_gyventojai;

    int gyventoju_skaicius()
    {
        int sum = 0;
        for (int i = 0; i < miestu_gyventojai.size(); i++)
        {
            sum += miestu_gyventojai[i];
        }
        return sum;
    }

    int maziausias_gyventoju_skaicius()
    {
        int min = miestu_gyventojai[0];
        for (int i = 0; i < miestu_gyventojai.size(); i++)
        {
            if (miestu_gyventojai[i] < min)
            {
                min = miestu_gyventojai[i];
            }
        }
        return min;
    }
};

struct Rezultatas
{
    int apskriciu_kiekis;
    vector<string> apskritis;
    vector<int> maziausias_gyventoju_sk;
    vector<int> gyventoju_sk;
};

void skaitymas(vector<Apskritis> &Apskritys)
{
    ifstream data("U2.txt");

    char miestas_ir_apskritis[34];

    int miesto_gyventojai;

    int miestu_skaicius;

    data >> miestu_skaicius;

    for (int i = 0; i < miestu_skaicius; i++)
    {
        string apskritis;
        Apskritis temp_apskritis;

        data.read(miestas_ir_apskritis, 1);
        data.read(miestas_ir_apskritis, 33);
        for (int j = 20; j < 33; j++)
        {
            if (miestas_ir_apskritis[j] != '\n')
            {
                apskritis += miestas_ir_apskritis[j];
            }
        }

        data >> miesto_gyventojai;

        int egzistuojacios_apskrities_indeksas = -1;
        for (int j = 0; j < Apskritys.size(); j++)
        {
            if (apskritis == Apskritys[j].pavadinimas)
            {
                egzistuojacios_apskrities_indeksas = j;
                break;
            }
        }

        if (egzistuojacios_apskrities_indeksas != -1)
        {
            Apskritys[egzistuojacios_apskrities_indeksas].miestu_gyventojai.push_back(miesto_gyventojai);
            continue;
        }

        temp_apskritis.pavadinimas = apskritis;
        temp_apskritis.miestu_gyventojai.push_back(miesto_gyventojai);
        Apskritys.push_back(temp_apskritis);
    }
}

void resultatu_perrasymas(vector<Apskritis> apskritys, Rezultatas &resultatu_struktura)
{
    resultatu_struktura.apskriciu_kiekis = apskritys.size();
    for (int i = 0; i < apskritys.size(); i++)
    {
        resultatu_struktura.apskritis.push_back(apskritys[i].pavadinimas);
        resultatu_struktura.maziausias_gyventoju_sk.push_back(apskritys[i].maziausias_gyventoju_skaicius());
        resultatu_struktura.gyventoju_sk.push_back(apskritys[i].gyventoju_skaicius());
    }
}

void sort(vector<Apskritis> &apskritys)
{
    for (int i = 0; i < apskritys.size(); i++)
    {
        for (int j = 0; j < apskritys.size() - 1 - i; j++)
        {
            if (apskritys[j].gyventoju_skaicius() > apskritys[j + 1].gyventoju_skaicius())
            {
                swap(apskritys[j], apskritys[j + 1]);
            }
            else if (apskritys[j].gyventoju_skaicius() == apskritys[j + 1].gyventoju_skaicius())
            {

                for (int k = 0; k < min(apskritys[j].pavadinimas.size(), apskritys[j + 1].pavadinimas.size()); k++)
                {
                    if (apskritys[j].pavadinimas[k] > apskritys[j + 1].pavadinimas[k])
                    {
                        swap(apskritys[j], apskritys[j + 1]);
                        break;
                    }
                }
            }
        }
    }
}

void rez(Rezultatas resultatu_struktura)
{
    ofstream rez("U2rez.txt");
    rez << resultatu_struktura.apskriciu_kiekis << endl;
    for (int i = 0; i < resultatu_struktura.apskriciu_kiekis; i++)
    {
        rez << resultatu_struktura.apskritis[i] << resultatu_struktura.maziausias_gyventoju_sk[i] << " " << resultatu_struktura.gyventoju_sk[i] << endl;
    }
}

void atspausdinti_apskritis(vector<Apskritis> apskritys)
{
    cout << "asdf\n";
    for (int i = 0; i < apskritys.size(); i++)
    {
        cout << apskritys[i].pavadinimas << endl;
        for (int j = 0; j < apskritys[i].miestu_gyventojai.size(); j++)
        {
            cout << apskritys[i].miestu_gyventojai[j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<Apskritis> apskritys;
    Rezultatas resultatu_struktura;
    skaitymas(apskritys);
    // atspausdinti_apskritis(apskritys);
    sort(apskritys);
    resultatu_perrasymas(apskritys, resultatu_struktura);
    rez(resultatu_struktura);
}