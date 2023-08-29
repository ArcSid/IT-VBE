#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Atskiras_pratimas
{
    string pavadinimas;
    string diena;
    int laikas;
};

struct Pratimas
{
    string pavadinimas;
    vector<string> dienos;
    vector<int> laikai;
    int laikas()
    {
        int sum = 0;
        for (int i = 0; i < laikai.size(); i++)
        {
            sum += laikai[i];
        }
        return sum;
    }
    int kiekis_ryte()
    {
        int kiekis_ryte = 0;
        for (int i = 0; i < dienos.size(); i++)
        {
            if (dienos[i] == "Rytas   ")
            {
                kiekis_ryte++;
            }
        }
        return kiekis_ryte;
    }

    int kiekis_diena()
    {
        int kiekis_diena = 0;
        for (int i = 0; i < dienos.size(); i++)
        {
            if (dienos[i] == "Diena   ")
            {
                kiekis_diena++;
            }
        }
        return kiekis_diena;
    }

    int kiekis_vakare()
    {
        int kiekis_vakare = 0;
        for (int i = 0; i < dienos.size(); i++)
        {
            if (dienos[i] == "Vakaras ")
            {
                kiekis_vakare++;
            }
        }
        return kiekis_vakare;
    }

    int kiek_kartu_atliko()
    {
        return kiekis_ryte() + kiekis_diena() + kiekis_vakare();
    }
};

void skaitymas(int &dienu_kiekis, int &atskiru_pratimu_kiekis, Atskiras_pratimas atskiri_pratimai[])
{
    ifstream data("U2.txt");
    data >> dienu_kiekis;
    for (int i = 0; i < dienu_kiekis; i++)
    {
        int kiekis;
        data >> kiekis;
        for (int j = 0; j < kiekis; j++)
        {
            char ch[16];
            data.read(ch, 1);
            data.read(ch, 15);
            atskiri_pratimai[atskiru_pratimu_kiekis].pavadinimas = ch;
            char ch_1[9];
            data.read(ch_1, 8);
            atskiri_pratimai[atskiru_pratimu_kiekis].diena = ch_1;
            data >> atskiri_pratimai[atskiru_pratimu_kiekis].laikas;
            atskiru_pratimu_kiekis++;
        }
        char endline[2];
        data.read(endline, 1);
    }
    data.close();
}

void unikalus_pratimai(int kiekis, Atskiras_pratimas atskiri_pratimai[], vector<Pratimas> &pratimai)
{
    for (int i = 0; i < kiekis; i++)
    {
        int egzistuoja_pratimas = false;
        for (int j = 0; j < pratimai.size(); j++)
        {
            if (pratimai[j].pavadinimas == atskiri_pratimai[i].pavadinimas)
            {
                pratimai[j].dienos.push_back(atskiri_pratimai[i].diena);
                pratimai[j].laikai.push_back(atskiri_pratimai[i].laikas);
                egzistuoja_pratimas = true;
            }
        }
        if (!egzistuoja_pratimas)
        {
            Pratimas laikinas_pratimas;
            laikinas_pratimas.pavadinimas = atskiri_pratimai[i].pavadinimas;
            laikinas_pratimas.dienos.push_back(atskiri_pratimai[i].diena);
            laikinas_pratimas.laikai.push_back(atskiri_pratimai[i].laikas);
            pratimai.push_back(laikinas_pratimas);
        }
    }
}

void sort_alphabetically(vector<Pratimas> &pratimai)
{
    for (int i = 0; i < pratimai.size() - 1; i++)
    {
        for (int j = 0; j < pratimai.size() - 1 - i; j++)
        {
            if (string(pratimai[j].pavadinimas) > string(pratimai[j + 1].pavadinimas))
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
        rez << pratimai[i].pavadinimas << pratimai[i].kiek_kartu_atliko() << " " << pratimai[i].laikas() << endl;
        if (pratimai[i].kiekis_ryte() != 0)
        {
            rez << "Ryte    " << pratimai[i].kiekis_ryte() << endl;
        }
        if (pratimai[i].kiekis_diena() != 0)
        {
            rez << "Diena   " << pratimai[i].kiekis_diena() << endl;
        }
        if (pratimai[i].kiekis_vakare() != 0)
        {
            rez << "Vakaras " << pratimai[i].kiekis_vakare() << endl;
        }
    }
    rez.close();
}

int main()
{
    Atskiras_pratimas atskiri_pratimai[93];
    int dienu_kiekis;
    int atskiru_pratimu_kiekis = 0;

    skaitymas(dienu_kiekis, atskiru_pratimu_kiekis, atskiri_pratimai);

    vector<Pratimas> pratimai;

    unikalus_pratimai(atskiru_pratimu_kiekis, atskiri_pratimai, pratimai);

    sort_alphabetically(pratimai);

    rez(pratimai);

    return 0;
}