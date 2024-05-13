#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Dalyvis
{
    string vardas;
    string miestas;
    int surinktiZodziai;
    int klaiduSk;
    int taskai;
};

void skaitytiIsFailo(int &dalyviuKiekis, Dalyvis dalyviai[])
{
    ifstream data("U2.txt");
    int miestuSk;
    data >> miestuSk;
    
    for (int i = 0; i < miestuSk; i++)
    {
        char ch[16];
        data.ignore();
        data.get(ch, 15);
        string miestas = ch;
        int miestoDalyviuSk;
        data >> miestoDalyviuSk;

        for (int j = 0; j < miestoDalyviuSk; j++)
        {
            char dalyvioVardas[11];
            data.ignore();
            data.get(dalyvioVardas, 10);
            dalyviai[dalyviuKiekis].vardas = dalyvioVardas;
            data >> dalyviai[dalyviuKiekis].surinktiZodziai >> dalyviai[dalyviuKiekis].klaiduSk;
            dalyviai[dalyviuKiekis].taskai = dalyviai[dalyviuKiekis].surinktiZodziai - 10 * dalyviai[dalyviuKiekis].klaiduSk;
            dalyviai[dalyviuKiekis].miestas = miestas;
            dalyviuKiekis++;
        }
    }
    data.close();
}

void rikiuotiPagalKlaidas(int dalyviukiekis, Dalyvis dalyviai[])
{
    for (int i = 0; i < dalyviukiekis; i++)
    {
        for (int j = 0; j < dalyviukiekis - i - 1; j++)
        {
            if (dalyviai[j].klaiduSk > dalyviai[j + 1].klaiduSk)
            {
                swap(dalyviai[j], dalyviai[j + 1]);
            }
            else if (dalyviai[j].klaiduSk == dalyviai[j + 1].klaiduSk && dalyviai[j].taskai < dalyviai[j + 1].taskai)
            {
                swap(dalyviai[j], dalyviai[j + 1]);
            }
        }
    }
}

void atrinktiSarasus(int &daugiausiaiTasku, int dalyviuKiekis, Dalyvis dalyviai[], int &diskvalifikuotuKiekis, string diskvalifikuoti[], int &geriausiuKiekis, Dalyvis geriausiDalyviai[])
{
    int max_i = 0;
    for (int i = 0; i < dalyviuKiekis; i++)
    {
        if (dalyviai[i].klaiduSk > 5)
        {
            diskvalifikuoti[diskvalifikuotuKiekis] = dalyviai[i].vardas;
            diskvalifikuotuKiekis++;
            continue;
        }

        if (dalyviai[max_i].taskai < dalyviai[i].taskai)
        {
            max_i = i;
        }

        geriausiDalyviai[geriausiuKiekis] = dalyviai[i];
        geriausiuKiekis++;
    }
    daugiausiaiTasku = dalyviai[max_i].taskai;
}

void rez(int daugiausiaiTasku, int geriausiuKiekis, Dalyvis geriausiDalyviai[], int diskvalifikuotuKiekis, string diskvalifikuoti[])
{
    ofstream rez("U2rez.txt");
    rez << daugiausiaiTasku << endl;
    for (int i = 0; i < 2 && i < geriausiuKiekis; i++)
    {
        rez << geriausiDalyviai[i].vardas << " " << geriausiDalyviai[i].miestas << endl;
    }

    if (diskvalifikuotuKiekis > 0)
    {
        rez << "Diskvalifikuoti:" << endl;
        for (int i = 0; i < diskvalifikuotuKiekis; i++)
        {
            rez << diskvalifikuoti[i] << endl;
        }
    }
    rez.close();
}

int main()
{
    Dalyvis dalyviai[50];
    int dalyviuKiekis = 0;

    int diskvalifikuotuKiekis = 0;
    string diskvalifikuoti[50];
    int geriausiuKiekis = 0;
    Dalyvis geriausiDalyviai[50];
    int daugiausiaiTasku;

    skaitytiIsFailo(dalyviuKiekis, dalyviai);
    atrinktiSarasus(daugiausiaiTasku, dalyviuKiekis, dalyviai, diskvalifikuotuKiekis, diskvalifikuoti, geriausiuKiekis, geriausiDalyviai);
    rikiuotiPagalKlaidas(geriausiuKiekis, geriausiDalyviai);
    rez(daugiausiaiTasku, geriausiuKiekis, geriausiDalyviai, diskvalifikuotuKiekis, diskvalifikuoti);
    return 0;
}
