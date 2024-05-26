#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Mokinys
{
    string vardas;
    vector<string> zymes;
    int laimejimuKiekis = 0;
    int lygiujuKiekis = 0;
    int pralaimejimuKiekis = 0;
};

void skaitymas(int &mokiniuKiekis, Mokinys mokiniai[])
{
    ifstream data("U2.txt");
    int zymiuKiekis;
    char ch[14];
    string zyme;

    data >> mokiniuKiekis >> zymiuKiekis;

    for (int i = 0; i < mokiniuKiekis; i++)
    {
        data.ignore();
        data.read(ch, 13);

        mokiniai[i].vardas = ch;
        for (int j = 0; j < zymiuKiekis; j++)
        {
            data >> zyme;
            mokiniai[i].zymes.push_back(zyme);
        }
    }
    data.close();
}

void mokiniuLyginimas(Mokinys &mok1, Mokinys mok2)
{
    for (int i = 0; i < mok1.zymes.size(); i++)
    {
        if (mok1.zymes[i] == mok2.zymes[i])
        {
            mok1.lygiujuKiekis++;
        }
        else if (mok1.zymes[i] == "A" && mok2.zymes[i] == "Z")
        {
            mok1.laimejimuKiekis++;
        }
        else if (mok1.zymes[i] == "A" && mok2.zymes[i] == "P")
        {
            mok1.pralaimejimuKiekis++;
        }
        else if (mok1.zymes[i] == "Z" && mok2.zymes[i] == "A")
        {
            mok1.pralaimejimuKiekis++;
        }
        else if (mok1.zymes[i] == "Z" && mok2.zymes[i] == "P")
        {
            mok1.laimejimuKiekis++;
        }
        else if (mok1.zymes[i] == "P" && mok2.zymes[i] == "A")
        {
            mok1.laimejimuKiekis++;
        }
        else if (mok1.zymes[i] == "P" && mok2.zymes[i] == "Z")
        {
            mok1.pralaimejimuKiekis++;
        }
    }
}

void rez(int mokiniuKiekis, Mokinys mokiniai[])
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < mokiniuKiekis; i++)
    {
        rez << mokiniai[i].vardas << " " << fixed << setprecision(2) << (float)mokiniai[i].laimejimuKiekis / mokiniai[i].pralaimejimuKiekis << " " << mokiniai[i].lygiujuKiekis << endl;
    }
    rez.close();
}

int main()
{
    int mokiniuKiekis;
    Mokinys mokiniai[30];
    skaitymas(mokiniuKiekis, mokiniai);

    for (int i = 0; i < mokiniuKiekis; i++)
    {
        for (int j = 0; j < mokiniuKiekis; j++)
        {
            if (i != j)
            {
                mokiniuLyginimas(mokiniai[i], mokiniai[j]);
            }
        }
    }

    rez(mokiniuKiekis, mokiniai);
    return 0;
}