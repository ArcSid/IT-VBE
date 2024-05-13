#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Valstybe
{
    vector<string> universitetai;
    vector<int> reitingai;
    string pavadinimas;
    int didziausioReitingoIndikatorius;
};

int didziausioReitingoIndikatoriausRadimas(vector<int> reitingai)
{
    int max_i = 0;
    for (int i = 0; i < reitingai.size(); i++)
    {
        if (reitingai[max_i] < reitingai[i])
        {
            max_i = i;
        }
    }
    return max_i;
}

void skaitymas(int &valstybiuKiekis, Valstybe valstybes[])
{
    ifstream data("U2.txt");
    data >> valstybiuKiekis;
    for (int i = 0; i < valstybiuKiekis; i++)
    {

        data.ignore(1);
        char pavadinimasChar[16];
        data.read(pavadinimasChar, 15);
        pavadinimasChar[15] = '\0';
        valstybes[i].pavadinimas = pavadinimasChar;

        int universitetuKiekis;
        data >> universitetuKiekis;

        for (int j = 0; j < universitetuKiekis; j++)
        {
            data.ignore(1);
            char ch[30];
            data.read(ch, 29);
            ch[30] = '\0';
            string universitetoPavadinimas = ch;
            int reitingas;
            data >> reitingas;
            valstybes[i].reitingai.push_back(reitingas);
            valstybes[i].universitetai.push_back(universitetoPavadinimas);
        }
    }
    data.close();
}

void sort(int valstybiuKiekis, Valstybe valstybes[])
{
    for (int i = 0; i < valstybiuKiekis; i++)
    {
        for (int j = 0; j < valstybiuKiekis - i - 1; j++)
        {
            if (valstybes[j].reitingai[valstybes[j].didziausioReitingoIndikatorius] < valstybes[j + 1].reitingai[valstybes[j + 1].didziausioReitingoIndikatorius])
            {
                swap(valstybes[j], valstybes[j + 1]);
            }
        }
    }
}

void rez(int valstybiuKiekis, Valstybe valstybes[])
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < valstybiuKiekis; i++)
    {
        rez << valstybes[i].pavadinimas << " " << valstybes[i].universitetai[valstybes[i].didziausioReitingoIndikatorius] << " " << valstybes[i].reitingai[valstybes[i].didziausioReitingoIndikatorius] << endl;
    }
    rez.close();
}

int main()
{
    int valstybiuKiekis;
    Valstybe valstybes[100];
    skaitymas(valstybiuKiekis, valstybes);

    for (int i = 0; i < valstybiuKiekis; i++)
    {
        valstybes[i].didziausioReitingoIndikatorius = didziausioReitingoIndikatoriausRadimas(valstybes[i].reitingai);
    }

    sort(valstybiuKiekis, valstybes);

    rez(valstybiuKiekis, valstybes);

    return 0;
}
