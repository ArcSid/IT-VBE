#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int minimum(vector<int> arr)
{
    int min_i = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[min_i] > arr[i])
        {
            min_i = i;
        }
    }
    return arr[min_i];
}

int maximum(vector<int> arr)
{
    int max_i = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[max_i] < arr[i])
        {
            max_i = i;
        }
    }
    return arr[max_i];
}

struct Komanda
{
    string pavadinimas;
    vector<int> teisejai_1;
    vector<int> teisejai_2;
    int taskaiUzTechnika()
    {
        int int1 = maximum(teisejai_1);
        int int2 = minimum(teisejai_1);
        int atimti = int1 + int2;
        int sum = 0;
        for (int i = 0; i < teisejai_1.size(); i++)
        {
            sum += teisejai_1[i];
        }
        return sum - atimti;
    }
    int taskaiUzArtistiskuma()
    {
        int atimti = maximum(teisejai_2) + minimum(teisejai_2);
        int sum = 0;
        for (int i = 0; i < teisejai_2.size(); i++)
        {
            sum += teisejai_2[i];
        }
        return sum - atimti;
    }

    int taskuSuma;
};

void formatavimas(vector<Komanda> &komandos)
{
    for (int i = 0; i < komandos.size(); i++)
    {
        komandos[i].taskuSuma = komandos[i].taskaiUzArtistiskuma() + komandos[i].taskaiUzTechnika();
    }
}

void sort(vector<Komanda> &komandos)
{
    for (int i = 0; i < komandos.size(); i++)
    {
        for (int j = 0; j < komandos.size() - 1 - i; j++)
        {
            if (komandos[j].taskuSuma < komandos[j + 1].taskuSuma)
            {
                swap(komandos[j], komandos[j + 1]);
            }
        }
    }
}

void skaitymas(vector<Komanda> &komandos)
{
    ifstream data("U2.txt");
    int a, b, c;
    data >> a >> b >> c;
    for (int i = 0; i < a; i++)
    {
        char ch[21];
        data.ignore();
        data.read(ch, 20);
        ch[20] = '\0';
        Komanda tempKomanda;
        tempKomanda.pavadinimas = ch;
        int temp;
        for (int j = 0; j < b; j++)
        {
            data >> temp;
            tempKomanda.teisejai_1.push_back(temp);
        }
        for (int j = 0; j < c; j++)
        {
            data >> temp;
            tempKomanda.teisejai_2.push_back(temp);
        }
        komandos.push_back(tempKomanda);
    }
    data.close();
}

void rez(vector<Komanda> komandos)
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < komandos.size(); i++)
    {
        rez << komandos[i].pavadinimas << " " << komandos[i].taskuSuma << endl;
    }
    rez.close();
}

int main()
{
    vector<Komanda> komandos;
    skaitymas(komandos);
    formatavimas(komandos);
    sort(komandos);
    rez(komandos);
    return 0;
}