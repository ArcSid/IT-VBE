#include <iostream>
#include <fstream>

using namespace std;

struct Avis
{
    string vardas;
    int sutapimo_koeficientas;
    string dnr_fragmentas;
    bool tiriama = false;
};

void skaitymas(Avis avys[], int &aviu_kiekis, int &tiriama_avis, int &fragmento_ilgis)
{
    ifstream data("U2.txt");
    data >> aviu_kiekis >> fragmento_ilgis >> tiriama_avis;
    char ch[41] = {""};
    for (int i = 0; i < aviu_kiekis; i++)
    {

        string vardas = "";
        string dnr = "";

        data.read(ch, 1);
        data.read(ch, 10 + fragmento_ilgis);

        for (int j = 0; j < 10; j++)
        {
            vardas += ch[j];
        }

        for (int j = 10; j < fragmento_ilgis + 11; j++)
        {
            dnr += ch[j];
        }

        avys[i].vardas = vardas;
        avys[i].dnr_fragmentas = dnr;
    }
}

int sutapimo_koeficientas(Avis tiriama_avis, Avis tikrinama_avis, int fragmento_ilgis)
{

    int sutapimas = 0;

    for (int i = 0; i < fragmento_ilgis; i++)
    {
        if (tiriama_avis.dnr_fragmentas[i] == tikrinama_avis.dnr_fragmentas[i])
        {
            sutapimas++;
        }
    }

    return sutapimas;
}

void sort(int aviu_kiekis, Avis avys[])
{
    for (int i = 0; i < aviu_kiekis; i++)
    {
        for (int j = 0; j < aviu_kiekis - 1 - i; j++)
        {
            if (avys[i].sutapimo_koeficientas > avys[i + 1].sutapimo_koeficientas && !avys[i].tiriama && !avys[i + 1].tiriama)
            {
                swap(avys[i + 1], avys[i]);
            }
        }
    }
}

void rez(int aviu_kiekis, Avis avys[])
{

    ofstream rez("U2rez.txt");

    for (int i = 0; i < aviu_kiekis; i++)
    {
        if (avys[i].tiriama)
        {
            rez << avys[i].vardas << endl;
            break;
        }
    }

    for (int i = 0; i < aviu_kiekis; i++)
    {
        if (avys[i].tiriama)
        {
            continue;
        }
        rez << avys[i].vardas << avys[i].sutapimo_koeficientas << endl;
    }
}

int main()
{
    Avis avys[20];
    int aviu_kiekis;
    int tiriama_avis;
    int fragmento_ilgis;

    skaitymas(avys, aviu_kiekis, tiriama_avis, fragmento_ilgis);

    for (int i = 0; i < aviu_kiekis; i++)
    {
        if (i == tiriama_avis - 1)
        {
            avys[i].tiriama = true;
            continue;
        }
        avys[i].sutapimo_koeficientas = sutapimo_koeficientas(avys[tiriama_avis - 1], avys[i], fragmento_ilgis);
    }

    sort(aviu_kiekis, avys);

    rez(aviu_kiekis, avys);
}