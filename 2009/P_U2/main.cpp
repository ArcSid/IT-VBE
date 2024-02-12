#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
struct Plaukikas
{
    string vardas;
    int minutes;
    int sekundes;
    int laikasSec()
    {
        return minutes * 60 + sekundes;
    }
};

void skaitymas(vector<Plaukikas> &plaukikai)
{
    ifstream data("U2.txt");
    int n;
    data >> n;
    for (int i = 0; i < n; i++)
    {
        int grupesNariuKiekis;
        data >> grupesNariuKiekis;
        for (int j = 0; j < grupesNariuKiekis; j++)
        {
            Plaukikas tempPlaukikas;
            char ch[21];
            data.read(ch, 1);
            data.read(ch, 20);
            ch[20] = '\0';
            tempPlaukikas.vardas = ch;
            data >> tempPlaukikas.minutes >> tempPlaukikas.sekundes;
            plaukikai.push_back(tempPlaukikas);
        }
    }
    data.close();
}

void sort(vector<Plaukikas> &plaukikai)
{
    for (int i = 0; i < plaukikai.size(); i++)
    {
        for (int j = 0; j < plaukikai.size() - 1 - i; j++)
        {
            if (plaukikai[j].laikasSec() > plaukikai[j + 1].laikasSec())
            {
                swap(plaukikai[j], plaukikai[j + 1]);
            }
        }
    }
}

void rez(vector<Plaukikas> plaukikai)
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < 5; i++)
    {
        rez << plaukikai[i].vardas << " " << plaukikai[i].minutes << " " << plaukikai[i].sekundes << endl;
    }
    rez.close();
}

int main()
{
    vector<Plaukikas> plaukikai;
    skaitymas(plaukikai);
    sort(plaukikai);
    rez(plaukikai);
    return 0;
}