#include <iostream>
#include <fstream>
using namespace std;

const int pilnoKomplektoDetaliuKiekiai[6] = {8, 2, 2, 2, 1, 1};

void skaitymas(int turimos_figureles[])
{
    ifstream data("U1.txt");
    int n;
    int trukstamuDetaliuKiekis;
    data >> n;
    for (int i = 0; i < n; i++)
    {
        for (int i = 0; i < 6; i++)
        {
            data >> trukstamuDetaliuKiekis;
            turimos_figureles[i] += pilnoKomplektoDetaliuKiekiai[i] - trukstamuDetaliuKiekis;
        }
    }
}

int kiekRinkiniu(int turimos_figureles[])
{
    turimos_figureles[0] = turimos_figureles[0] / pilnoKomplektoDetaliuKiekiai[0];
    turimos_figureles[1] = turimos_figureles[1] / pilnoKomplektoDetaliuKiekiai[1];
    turimos_figureles[2] = turimos_figureles[2] / pilnoKomplektoDetaliuKiekiai[2];
    turimos_figureles[3] = turimos_figureles[3] / pilnoKomplektoDetaliuKiekiai[3];

    int maziausiasRinkiniuKiekis = turimos_figureles[0];
    for (int i = 0; i < 6; i++)
    {
        if (maziausiasRinkiniuKiekis > turimos_figureles[i])
        {
            maziausiasRinkiniuKiekis = turimos_figureles[i];
        }
    }
    return maziausiasRinkiniuKiekis;
}

void rez(int maziausiasRinkiniuKiekis)
{
    ofstream rez("U1rez.txt");
    rez << maziausiasRinkiniuKiekis << endl;
}

int main()
{
    int turimos_figureles[6] = {0};
    skaitymas(turimos_figureles);
    rez(kiekRinkiniu(turimos_figureles));
    return 0;
}