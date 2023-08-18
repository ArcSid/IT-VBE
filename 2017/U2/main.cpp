#include <iostream>
#include <fstream>

using namespace std;

struct Staciakampis
{
    int x_pos;
    int y_pos;

    int plotis;
    int ilgis;

    int r;
    int g;
    int b;
};

void skaitymas(int &x_max, int &y_max, int &kiekis, Staciakampis staciakampiai[])
{
    ifstream data("U2.txt");
    data >> kiekis;

    for (int i = 0; i < kiekis; i++)
    {
        data >> staciakampiai[i].x_pos;
        data >> staciakampiai[i].y_pos;
        data >> staciakampiai[i].plotis;
        data >> staciakampiai[i].ilgis;
        data >> staciakampiai[i].r;
        data >> staciakampiai[i].g;
        data >> staciakampiai[i].b;

        int x_galas = staciakampiai[i].x_pos + staciakampiai[i].plotis;
        if (x_galas > x_max)
        {
            x_max = x_galas;
        }
        int y_galas = staciakampiai[i].y_pos + staciakampiai[i].ilgis;
        if (y_galas > y_max)
        {
            y_max = y_galas;
        }
    }
    data.close();
}

void uzdeti_staciakampi(int piesinys[][100][3], Staciakampis rect)
{
    for (int x = rect.x_pos; x < rect.x_pos + rect.plotis; x++)
    {
        for (int y = rect.y_pos; y < rect.y_pos + rect.ilgis; y++)
        {
            piesinys[y][x][0] = rect.r;
            piesinys[y][x][1] = rect.g;
            piesinys[y][x][2] = rect.b;
        }
    }
}

void print_piesinys(int p[][100][3])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (p[i][j][0] == 255 && p[i][j][1] == 255 && p[i][j][2] == 255)
            {
                cout << "0 ";
            }
            else
            {
                cout << "1 ";
            }
        }
        cout << endl;
    }
}

void rez(int x_max, int y_max, int piesinys[][100][3])
{
    ofstream rez("U2rez.txt");
    rez << y_max << " " << x_max << endl;
    for (int x = 0; x < y_max; x++)
    {
        for (int y = 0; y < x_max; y++)
        {
            rez << piesinys[x][y][0] << " " << piesinys[x][y][1] << " " << piesinys[x][y][2] << endl;
        }
    }
    rez.close();
}

void empty_board(int piesinys[][100][3])
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                piesinys[i][j][k] = 255;
            }
        }
    }
}

int main()
{

    Staciakampis staciakampiai[100];
    int staciakampiu_sk;
    int piesinys[100][100][3];
    int x_max = 0, y_max = 0;
    empty_board(piesinys);
    skaitymas(x_max, y_max, staciakampiu_sk, staciakampiai);

    for (int i = 0; i < staciakampiu_sk; i++)
    {
        uzdeti_staciakampi(piesinys, staciakampiai[i]);
    }
    rez(x_max, y_max, piesinys);
    // print_piesinys(piesinys);
    return 0;
}
