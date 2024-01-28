#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Stotele
{
    string pavadinimas;
    int marsrutu_kiekis;
    vector<int> marsrutai;
};

struct Marsrutas
{
    int numeris;
    vector<string> stoteles;
};

void skaitymas(int &stoteliu_sk, Stotele stoteles[])
{
    ifstream data("U2.txt");
    data >> stoteliu_sk;
    for (int i = 0; i < stoteliu_sk; i++)
    {
        char name[21];
        data.read(name, 1);
        data.read(name, 20);
        name[20] = '\0';
        stoteles[i].pavadinimas = name;
        data >> stoteles[i].marsrutu_kiekis;
        for (int a = 0; a < stoteles[i].marsrutu_kiekis; a++)
        {
            int b = 0;
            data >> b;
            stoteles[i].marsrutai.push_back(b);
        }
    }
}

void print_marsrutas(Marsrutas marsrutas)
{
    cout << marsrutas.numeris << " ";
    cout << marsrutas.stoteles.size() << "     ";
    for (int a = 0; a < marsrutas.stoteles.size(); a++)
    {
        cout << marsrutas.stoteles[a] << " ";
    }
    cout << endl;
}

void stotelesToMarsrutai(int stoteliu_sk, Stotele stoteles[], vector<Marsrutas> &marsrutai)
{

    for (int i = 0; i < stoteliu_sk; i++)
    {
        for (int a = 0; a < stoteles[i].marsrutai.size(); a++)
        {

            int egzistuojantis_marsrutas = -1;
            for (int b = 0; b < marsrutai.size(); b++)
            {
                if (marsrutai[b].numeris == stoteles[i].marsrutai[a])
                {
                    egzistuojantis_marsrutas = b;
                    break;
                }
            }
            if (egzistuojantis_marsrutas != -1)
            {
                marsrutai[egzistuojantis_marsrutas].stoteles.push_back(stoteles[i].pavadinimas);
            }
            else
            {
                Marsrutas marsrutas;
                marsrutas.numeris = stoteles[i].marsrutai[a];
                marsrutas.stoteles.push_back(stoteles[i].pavadinimas);
                marsrutai.push_back(marsrutas);
            }
        }
    }
}

Marsrutas ilgiausias_marsrutas(vector<Marsrutas> marsrutai)
{
    int max_i = 0;
    for (int i = 0; i < marsrutai.size(); i++)
    {
        if (marsrutai[i].stoteles.size() > marsrutai[max_i].stoteles.size())
        {
            max_i = marsrutai[i].stoteles.size();
        }
    }

    return marsrutai[max_i];
}
void resultatas(Marsrutas marsrutas)
{
    ofstream rez("U2rez.txt");
    rez << marsrutas.numeris << endl;
    for (int i = 0; i < marsrutas.stoteles.size(); i++)
    {
        rez << marsrutas.stoteles[i] << endl;
    }
}

int main()
{
    int stoteliu_sk;
    Stotele stoteles[100];
    vector<Marsrutas> marsrutai;
    skaitymas(stoteliu_sk, stoteles);
    stotelesToMarsrutai(stoteliu_sk, stoteles, marsrutai);
    Marsrutas ilgiausias_m = ilgiausias_marsrutas(marsrutai);
    resultatas(ilgiausias_m);
}