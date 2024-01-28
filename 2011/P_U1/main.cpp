#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int VYR = 3;
const int KAIRE = 1;

struct Pirstine
{
    int puse;
    int dydis;
    int lytis;
};

struct Pora
{
    int dydis;
    int m_k = 0;
    int m_d = 0;
    int v_k = 0;
    int v_d = 0;
};

void skaitymas(int &num, int lytis[], int rankosPuse[], int dydis[])
{
    ifstream data("U1.txt");
    data >> num;
    for (int i = 0; i < num; i++)
    {
        data >> lytis[i] >> rankosPuse[i] >> dydis[i];
    }
    data.close();
}

void formatavimas(int &num, int lytis[], int rankosPuse[], int dydis[],
                  vector<Pirstine> &pirstines)
{
    for (int i = 0; i < num; i++)
    {
        Pirstine tempPirstine;
        tempPirstine.dydis = dydis[i];
        tempPirstine.lytis = lytis[i];
        tempPirstine.puse = rankosPuse[i];
        pirstines.push_back(tempPirstine);
    }
}

void poruAtrinkimas(vector<Pirstine> pirstines, vector<Pora> &sudetos_pirstines)
{
    for (int i = 0; i < pirstines.size(); i++)
    {
        bool dydisEgzistuoja = false;
        int egzistuojantiPirstine_i = -1;
        Pora pirst;
        for (int j = 0; j < sudetos_pirstines.size(); j++)
        {
            if (pirstines[i].dydis == sudetos_pirstines[j].dydis)
            {
                pirst = sudetos_pirstines[j];
                egzistuojantiPirstine_i = j;
                dydisEgzistuoja = true;

                break;
            }
        }

        if (pirstines[i].lytis == VYR)
        {
            if (pirstines[i].puse == KAIRE)
            {
                pirst.v_k++;
            }
            else
            {
                pirst.v_d++;
            }
        }
        else
        {
            if (pirstines[i].puse == KAIRE)
            {
                pirst.m_k++;
            }
            else
            {
                pirst.m_d++;
            }
        }

        if (!dydisEgzistuoja)
        {
            pirst.dydis = pirstines[i].dydis;
            sudetos_pirstines.push_back(pirst);
        }
        else
        {
            sudetos_pirstines[egzistuojantiPirstine_i] = pirst;
        }
    }
}

int kiekPoru(int kairiuKiekis, int desiniuKiekis)
{
    return min(kairiuKiekis, desiniuKiekis);
}

void rez(vector<Pora> sudetos_pirstines)
{
    ofstream rez("U1rez.txt");
    for (int i = 0; i < sudetos_pirstines.size(); i++)
    {
        int moteriskosPoros = kiekPoru(sudetos_pirstines[i].m_k, sudetos_pirstines[i].m_d);
        int vyriskosPoros = kiekPoru(sudetos_pirstines[i].v_k, sudetos_pirstines[i].v_d);

        if (moteriskosPoros + vyriskosPoros != 0)
        {
            rez << sudetos_pirstines[i].dydis << " " << moteriskosPoros << " " << vyriskosPoros << endl;
        }
    }
    rez.close();
}

void sort(vector<Pora> &sudetos_pirstines)
{
    for (int i = 0; i < sudetos_pirstines.size(); i++)
    {
        for (int j = 0; j < sudetos_pirstines.size() - 1 - i; j++)
        {
            if (sudetos_pirstines[j].dydis > sudetos_pirstines[j + 1].dydis)
            {
                swap(sudetos_pirstines[j], sudetos_pirstines[j + 1]);
            }
        }
    }
}

int main()
{
    int num;
    int lytis[100];
    int rankosPuse[100];
    int dydis[100];

    skaitymas(num, lytis, rankosPuse, dydis);

    vector<Pirstine> pirstines;
    formatavimas(num, lytis, rankosPuse, dydis, pirstines);

    vector<Pora> sudetos_pirstines;
    poruAtrinkimas(pirstines, sudetos_pirstines);
    sort(sudetos_pirstines);
    rez(sudetos_pirstines);
    return 0;
}
