#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Spalva
{
    int r;
    int g;
    int b;

    char sesioliktines_spalvos_simbolis(int n)
    {
        if (n >= 0 && n <= 9)
        {
            return '0' + n;
        }
        return 'A' + (n - 10);
    }

    string sesioliktine_spalva()
    {

        string str;

        str += sesioliktines_spalvos_simbolis(r / 16);
        str += sesioliktines_spalvos_simbolis(r % 16);
        str += sesioliktines_spalvos_simbolis(g / 16);
        str += sesioliktines_spalvos_simbolis(g % 16);
        str += sesioliktines_spalvos_simbolis(b / 16);
        str += sesioliktines_spalvos_simbolis(b % 16);

        return str;
    }
};

void skaitymas(int &kordinate_x, int &kordinate_y, vector<Spalva> &spalvos)
{

    ifstream data("U1.txt");

    data >> kordinate_x >> kordinate_y;

    Spalva laikina_spalva;

    for (int i = 0; i < kordinate_x * kordinate_y; i++)
    {

        data >> laikina_spalva.r;
        data >> laikina_spalva.g;
        data >> laikina_spalva.b;

        spalvos.push_back(laikina_spalva);
    }
    data.close();
}

void rez(int kordinate_x, int kordinate_y, vector<Spalva> spalvos)
{

    ofstream rez("U1rez.txt");

    int temp = 0;

    for (int j = 0; j < kordinate_x; j++)
    {

        for (int i = 0; i < kordinate_y; i++)
        {

            if (i == 0)
            {
                rez << spalvos[temp].sesioliktine_spalva();
                temp++;
                continue;
            }

            rez << ";" << spalvos[temp].sesioliktine_spalva();
            temp++;
        }
        rez << endl;
    }
    rez.close();
}

int main()
{
    vector<Spalva> spalvos;
    int kordinate_x;
    int kordinate_y;

    skaitymas(kordinate_x, kordinate_y, spalvos);

    rez(kordinate_x, kordinate_y, spalvos);

    return 0;
}