#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int minimumVertinimasIndikatorius(int vadovoVertinimas, int vertinimai[])
{
    int min_i = 0;
    for (int i = 0; i < 3; i++)
    {
        if (vertinimai[min_i] > vertinimai[i])
        {
            min_i = i;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (i != min_i)
        {
            if (vertinimai[min_i] == vertinimai[i])
            {
                return vadovoVertinimas - 1;
            }
        }
    }
    return min_i;
}

void skaitymas(int &n, int &vadovas, int darbuotojai[][3])
{
    ifstream data("U1.txt");
    data >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            data >> darbuotojai[i][j];
        }
    }
    data >> vadovas;
    data.close();
};

void minimaliuVertinimuSumavimas(int vadovas, int n, int vertinimai[], int darbuotojai[][3])
{
    for (int i = 0; i < n; i++)
    {
        vertinimai[minimumVertinimasIndikatorius(vadovas, darbuotojai[i])]++;
    }
}

int blogiausiasZaidimas(int vertinimai[])
{
    int min_i = 0;
    for (int i = 0; i < 3; i++)
    {
        if (vertinimai[min_i] > vertinimai[i])
        {
            min_i = i;
        }
    }
    return min_i + 1;
}

void rez(int blogiausias, int vertinimai[])
{
    ofstream rez("U1rez.txt");
    rez << vertinimai[0] << " " << vertinimai[1] << " " << vertinimai[2] << endl;
    rez << blogiausias << endl;
    rez.close();
}

int main()
{
    int vadovas;
    int n;
    int darbuotojai[10][3];
    skaitymas(n, vadovas, darbuotojai);

    int vertinimai[3] = {0};
    minimaliuVertinimuSumavimas(vadovas, n, vertinimai, darbuotojai);
    int blogiausias = blogiausiasZaidimas(vertinimai);
    rez(blogiausias, vertinimai);
    return 0;
}
