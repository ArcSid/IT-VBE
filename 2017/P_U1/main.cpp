#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Spalva
{
    string reiksme;
    int r;
    int g;
    int b;
};

int hexToInt(char hex)
{
    return hex < 48 + 10 ? hex - 48 : hex - 55;
}

int hexToInt(string hex)
{
    return 16 * hexToInt(hex[0]) + hexToInt(hex[1]);
}

void rgbReiksmes(vector<Spalva> &spalvos)
{
    for (int i = 0; i < spalvos.size(); i++)
    {
        spalvos[i].r = hexToInt(spalvos[i].reiksme.substr(0, 2));
        spalvos[i].g = hexToInt(spalvos[i].reiksme.substr(2, 2));
        spalvos[i].b = hexToInt(spalvos[i].reiksme.substr(4, 2));
    }
}

void skaitymas(int &x, int &y, vector<Spalva> &spalvos)
{
    int spalvuKiekis;
    Spalva temp;
    ifstream data("U1.txt");

    data >> x >> y;
    spalvuKiekis = x * y;

    for (int i = 0; i < spalvuKiekis; i++)
    {
        data >> temp.reiksme;
        spalvos.push_back(temp);
    }

    data.close();
}

void rez(int x, int y, vector<Spalva> spalvos)
{
    ofstream rez("U1rez.txt");
    for (int i = 0; i < spalvos.size(); i++)
    {
        bool kabliataskis = true;
        if (i % y == 0 && i != 0)
        {
            rez << endl;
        }
        if ((i + 1) % y)
        {
            kabliataskis = false;
        }
        rez << spalvos[i].r << " " << spalvos[i].g << " " << spalvos[i].b;
        if ((i + 1) % 3 != 0)
        {
            rez << ";";
        }
    }
    rez.close();
}

int main()
{
    vector<Spalva> spalvos;
    int x, y;
    skaitymas(x, y, spalvos);
    rgbReiksmes(spalvos);
    rez(x, y, spalvos);
    return 0;
}
