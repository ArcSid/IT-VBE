#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void skaitymas(int ilipimai[], int islipimai[])
{
    ifstream data("U1.txt");
    int stoteliu_kiekis;
    data >> stoteliu_kiekis;
    int stotele;
    int temp;
    for (int i = 0; i < stoteliu_kiekis; i++)
    {
        data >> stotele;
        data >> temp;
        if (temp < 0)
        {
            islipimai[stotele] += temp;
        }
        else
        {
            ilipimai[stotele] += temp;
        }
    }
}
int daugiausiai_keleiviu(int ilipimai[])
{
    int max = 0;
    int max_i = 0;
    for (int i = 0; i < 100; i++)
    {
        if (ilipimai[i] > max)
        {
            max = ilipimai[i];
            max_i = i;
        }
    }
    return max_i;
}

void rez(int ilipimai[], int islipimai[], int max)
{
    int stoteliu_sk;
    int numeriai[100] = {0};
    int numerio_islipimai[100] = {0};
    int numerio_ilipimai[100] = {0};
    int j = 0;
    for (int i = 0; i < 100; i++)
    {
        if (islipimai[i] < 0 || ilipimai[i] > 0)
        {
            numeriai[j] = i;
            numerio_ilipimai[j] = ilipimai[i];
            numerio_islipimai[j] = islipimai[i];
            j++;
        }
    }
    ofstream rez("U1rez.txt");
    for (int i = 0; i < j; i++)
    {
        rez << setw(6) << numeriai[i];
    }
    rez << endl;
    for (int i = 0; i < j; i++)
    {
        rez << setw(6) << numerio_ilipimai[i];
    }
    rez << endl;
    for (int i = 0; i < j; i++)
    {
        rez << setw(6) << numerio_islipimai[i];
    }
    rez << endl
        << setw(6) << max << endl;
}
int main()
{
    int ilipimai[100] = {0};
    int islipimai[100] = {0};
    skaitymas(ilipimai, islipimai);
    int max = daugiausiai_keleiviu(ilipimai);
    rez(ilipimai, islipimai, max);
}