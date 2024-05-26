#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct PradiniaiDuomenys
{
    string pavadinimasDavusios;
    string pavadinimasGavusios;
    int taskuKiekis = 0;
};

struct Salis
{
    string pavadinimas;
    int taskai = 0;
    int kiekKartuGavo12T = 0;
};

void skaitymas(vector<PradiniaiDuomenys> &duomenys)
{
    ifstream data("Eurovizija.csv");
    PradiniaiDuomenys tempDuomenys;
    string line;

    while (getline(data, line))
    {
        stringstream eilute(line);
        string saliesPavadinimas;

        getline(eilute, saliesPavadinimas, ';');
        tempDuomenys.pavadinimasDavusios = saliesPavadinimas;

        getline(eilute, saliesPavadinimas, ';');
        tempDuomenys.pavadinimasGavusios = saliesPavadinimas;

        getline(eilute, saliesPavadinimas, ';');
        tempDuomenys.taskuKiekis = stoi(saliesPavadinimas);
        duomenys.push_back(tempDuomenys);
    }
    data.close();
}

void surikiuotiPradiniusDuomenis(vector<PradiniaiDuomenys> &duomenys)
{
    for (int i = 0; i < duomenys.size(); i++)
    {
        for (int j = 0; j < duomenys.size() - 1 - i; j++)
        {
            if (duomenys[j].pavadinimasDavusios > duomenys[j + 1].pavadinimasDavusios)
            {
                swap(duomenys[j], duomenys[j + 1]);
            }
            else if (duomenys[j].pavadinimasDavusios == duomenys[j + 1].pavadinimasDavusios && duomenys[j].taskuKiekis < duomenys[j + 1].taskuKiekis)
            {
                swap(duomenys[j], duomenys[j + 1]);
            }
        }
    }
}

void irasytiSurikiuotaDuomenuSarasa(ofstream &rez, vector<PradiniaiDuomenys> duomenys)
{
    rez << "Pradinis sąrašas:" << endl;
    for (int i = 0; i < duomenys.size(); i++)
    {
        rez << duomenys[i].pavadinimasDavusios << " " << duomenys[i].pavadinimasGavusios << " " << duomenys[i].taskuKiekis << endl;
    }
    rez << endl;
}

void apskaiciuotiSaliuTaskus(vector<Salis> &salys, vector<PradiniaiDuomenys> duomenys)
{
    for (int i = 0; i < duomenys.size(); i++)
    {
        bool naujaSalis = true;
        for (int j = 0; j < salys.size(); j++)
        {
            if (duomenys[i].pavadinimasGavusios == salys[j].pavadinimas)
            {
                naujaSalis = false;
                salys[j].taskai += duomenys[i].taskuKiekis;
                break;
            }
        }
        if (naujaSalis)
        {
            Salis tempSalis;
            tempSalis.pavadinimas = duomenys[i].pavadinimasGavusios;
            tempSalis.taskai = duomenys[i].taskuKiekis;
            salys.push_back(tempSalis);
        }
    }
}

void surikiotiSalis(vector<Salis> &salys)
{
    for (int i = 0; i < salys.size(); i++)
    {
        for (int j = 0; j < salys.size() - 1 - i; j++)
        {
            if (salys[j].pavadinimas > salys[j + 1].pavadinimas)
            {
                swap(salys[j], salys[j + 1]);
            }
        }
    }
}

void pildytiDuomenuFailaSalimisIrJuGautaisTaskais(ofstream &rez, vector<Salis> salys)
{
    rez << "Šalių gauti taškai:" << endl;
    for (int i = 0; i < salys.size(); i++)
    {
        rez << salys[i].pavadinimas << " " << salys[i].taskai << endl;
    }
    rez << endl;
}

void atrinktiKiekKiekvienaSalisGavo12T(vector<Salis> &salys, vector<PradiniaiDuomenys> duomenys)
{
    for (int i = 0; i < duomenys.size(); i++)
    {
        if (duomenys[i].taskuKiekis == 12)
        {
            for (int j = 0; j < salys.size(); j++)
            {
                if (salys[j].pavadinimas == duomenys[i].pavadinimasGavusios)
                {
                    salys[j].kiekKartuGavo12T++;
                    break;
                }
            }
        }
    }
}

void rastiKiekDaugiausiai12TGavoIrJuSarasa(int &maxDaugiausiaiKartuSkirta12T, vector<string> &saliuSu12TSarasas, vector<Salis> salys)
{
    int max_i = 0;
    for (int i = 0; i < salys.size(); i++)
    {
        if (salys[i].kiekKartuGavo12T > salys[max_i].kiekKartuGavo12T)
        {
            max_i = i;
        }
    }
    maxDaugiausiaiKartuSkirta12T = salys[max_i].kiekKartuGavo12T;

    for (int i = 0; i < salys.size(); i++)
    {
        if (maxDaugiausiaiKartuSkirta12T == salys[i].kiekKartuGavo12T)
        {
            saliuSu12TSarasas.push_back(salys[i].pavadinimas);
        }
    }

    for (int i = 0; i < saliuSu12TSarasas.size(); i++)
    {
        for (int j = 0; j < saliuSu12TSarasas.size() - 1 - i; j++)
        {
            if (saliuSu12TSarasas[j] > saliuSu12TSarasas[j + 1])
            {
                swap(saliuSu12TSarasas[j], saliuSu12TSarasas[j + 1]);
            }
        }
    }
}

void papildytiDuomenuFailaSalimisKuriosSurinko12T(ofstream &rez, int maxDaugiausiaiKartuSkirta12T, vector<string> saliuSu12TSarasas)
{
    rez << "Daugiausiai " << maxDaugiausiaiKartuSkirta12T << " kartų(-us) vienai šaliai" << endl;
    rez << "buvo skirta 12 balų" << endl;

    rez << "Šios šalys yra: ";
    for (int i = 0; i < saliuSu12TSarasas.size(); i++)
    {
        rez << saliuSu12TSarasas[i] << " ";
    }
    rez << endl;
}

int main()
{
    vector<PradiniaiDuomenys> duomenys;
    ofstream rez("Rezultatai.txt");
    vector<Salis> salys;
    vector<string> saliuSu12TSarasas;
    int maxDaugiausiaiKartuSkirta12T;

    skaitymas(duomenys);
    surikiuotiPradiniusDuomenis(duomenys);
    irasytiSurikiuotaDuomenuSarasa(rez, duomenys);
    apskaiciuotiSaliuTaskus(salys, duomenys);
    surikiotiSalis(salys);
    pildytiDuomenuFailaSalimisIrJuGautaisTaskais(rez, salys);
    atrinktiKiekKiekvienaSalisGavo12T(salys, duomenys);
    rastiKiekDaugiausiai12TGavoIrJuSarasa(maxDaugiausiaiKartuSkirta12T, saliuSu12TSarasas, salys);
    papildytiDuomenuFailaSalimisKuriosSurinko12T(rez, maxDaugiausiaiKartuSkirta12T, saliuSu12TSarasas);
    rez.close();

    return 0;
}