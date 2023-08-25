#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Mokinys
{
    string vardas;
    int atliktos_uzduotys[12];
    int sugaistas_laikas;
    int taskai;
    int teisingu_kiekis;
};

void skaitymas(int &uzdaviniu_kiekis, int laiko_limitai[], int taskai_uz_uzdavinius[], vector<Mokinys> &mokiniai)
{
    ifstream data("U1.txt");
    data >> uzdaviniu_kiekis;
    for (int i = 0; i < uzdaviniu_kiekis; i++)
    {
        data >> laiko_limitai[i];
    }
    for (int i = 0; i < uzdaviniu_kiekis; i++)
    {
        data >> taskai_uz_uzdavinius[i];
    }

    string line;

    char ch[2];
    data.read(ch, 1);

    while (getline(data, line))
    {
        Mokinys temp_mokinys;

        string str = line.substr(0, 10);
        temp_mokinys.vardas = str;

        istringstream iss(line.substr(10));

        int num;

        for (int i = 0; i < uzdaviniu_kiekis; i++)
        {
            iss >> num;
            temp_mokinys.atliktos_uzduotys[i] = num;
        }
        mokiniai.push_back(temp_mokinys);
    }
    data.close();
}

void tasku_ir_laiko_skaiciavimas(vector<Mokinys> &mokiniai, int uzdaviniu_kiekis, int laiko_limitai[], int taskai_uz_uzdavinius[])
{
    for (int i = 0; i < mokiniai.size(); i++)
    {
        int laikas = 0;
        int teisingu_kiekis = 0;
        int taskai = 0;
        for (int j = 0; j < uzdaviniu_kiekis; j++)
        {
            if (mokiniai[i].atliktos_uzduotys[j] != 0)
            {

                if (mokiniai[i].atliktos_uzduotys[j] > laiko_limitai[j])
                {
                    taskai += taskai_uz_uzdavinius[j] / 2;
                }
                else
                {
                    taskai += taskai_uz_uzdavinius[j];
                }

                laikas += mokiniai[i].atliktos_uzduotys[j];
                teisingu_kiekis++;
            }
        }
        mokiniai[i].taskai = taskai;
        mokiniai[i].sugaistas_laikas = laikas;
        mokiniai[i].teisingu_kiekis = teisingu_kiekis;
    }
}

void sort(vector<Mokinys> &mokiniai)
{
    for (int i = 0; i < mokiniai.size() - 1; i++)
    {
        for (int j = 0; j < mokiniai.size() - 1 - i; j++)
        {
            if (mokiniai[j].teisingu_kiekis < mokiniai[j + 1].teisingu_kiekis || (mokiniai[j].teisingu_kiekis == mokiniai[j + 1].teisingu_kiekis && mokiniai[j].taskai < mokiniai[j + 1].taskai))
            {
                swap(mokiniai[j], mokiniai[j + 1]);
            }
        }
    }
}

void rez(vector<Mokinys> mokiniai)
{
    ofstream rez("U1rez.txt");
    int max = 0;
    for (int i = 0; i < mokiniai.size(); i++)
    {
        if (max < mokiniai[i].taskai)
        {
            max = mokiniai[i].taskai;
        }
    }
    rez << max << endl;
    for (int i = 0; i < mokiniai.size() - 1; i++)
    {
        rez << mokiniai[i].vardas << mokiniai[i].teisingu_kiekis << " " << mokiniai[i].sugaistas_laikas << endl;
    }
    rez.close();
}

int main()
{
    vector<Mokinys> mokiniai;
    int uzdaviniu_kiekis;
    int laiko_limitai[12];
    int taskai_uz_uzdavinius[12];
    skaitymas(uzdaviniu_kiekis, laiko_limitai, taskai_uz_uzdavinius, mokiniai);
    tasku_ir_laiko_skaiciavimas(mokiniai, uzdaviniu_kiekis, laiko_limitai, taskai_uz_uzdavinius);
    sort(mokiniai);

    rez(mokiniai);

    return 0;
}