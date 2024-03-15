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

int hexToInt(string hex)
{
    int result = 0;

    if (hex[0] - 48 < 10)
    {
        result += 16 * (hex[0] - 48);
    }
    else
    {
        result += 16 * (hex[0] - 55);
    }

    if (hex[1] - 48 < 10)
    {
        result += hex[1] - 48;
    }
    else
    {
        result += hex[1] - 55;
    }
    return result;
}

void rgbReiksmes(vector<Spalva> &spalvos)
{
    for (int i = 0; i < spalvos.size(); i++)
    {
        string dvizenklis = "";
        dvizenklis += spalvos[i].reiksme[0];
        dvizenklis += spalvos[i].reiksme[1];
        spalvos[i].r = hexToInt(dvizenklis);
        dvizenklis = "";
        dvizenklis += spalvos[i].reiksme[2];
        dvizenklis += spalvos[i].reiksme[3];
        spalvos[i].g = hexToInt(dvizenklis);
        dvizenklis = "";
        dvizenklis += spalvos[i].reiksme[4];
        dvizenklis += spalvos[i].reiksme[5];
        spalvos[i].b = hexToInt(dvizenklis);
        dvizenklis = "";
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
        if (i % y == 0 && i!=0)
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
