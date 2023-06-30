#include <iostream>
#include <fstream>
using namespace std;
void result(int sk, string stoteles[], int laikai[])
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < sk; i++)
    {
        rez << stoteles[i];
        int min = laikai[i] % 60;
        int val = (laikai[i] - min) / 60;
        rez << val << " val. " << min << " min." << endl;
    }
}
int laikas(int praeitos_stoteles_laikas, double kelias, int greitis)
{
    return praeitos_stoteles_laikas + kelias / greitis * 60;
}

void skaitymas(double atstumai_tarp_stoteliu[], int &autobuso_greitis, int &stoteliu_sk, int &isvykimo_laikas, string stoteles[])
{
    ifstream data("U2.txt");
    data >> stoteliu_sk;
    data >> autobuso_greitis;
    int temp = 0;
    data >> isvykimo_laikas;
    data >> temp;
    isvykimo_laikas *= 60;
    isvykimo_laikas += temp;

    for (int i = 0; i < stoteliu_sk; i++)
    {
        char name[16] = {0};
        data.read(name, 1);
        data.read(name, 15);
        stoteles[i] = name;
        data >> atstumai_tarp_stoteliu[i];
    }
}

int main()
{
    string stoteles[100];
    double atstumai_tarp_stoteliu[100];
    int autobuso_greitis;
    int stoteliu_sk = 0;
    int isvykimo_laikas;
    int laikai[100];
    skaitymas(atstumai_tarp_stoteliu, autobuso_greitis, stoteliu_sk, isvykimo_laikas, stoteles);

    laikai[0] = laikas(isvykimo_laikas, atstumai_tarp_stoteliu[0], autobuso_greitis);

    for (int i = 0; i < stoteliu_sk - 1; i++)
    {
        laikai[i + 1] = laikas(laikai[i], atstumai_tarp_stoteliu[i + 1], autobuso_greitis);
    }
    result(stoteliu_sk, stoteles, laikai);
}
