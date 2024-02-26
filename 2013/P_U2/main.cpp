#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Savivaldybe
{
    string pavadinimas;
    int mokykluSk = 0;
};

struct Apskritis
{
    string pavadinimas;
    vector<int> mokykluKiekiai;
    int maximum;
};

int maximum(vector<int> arr)
{
    int max = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

void skaitymas(int &savivaldybiuKiekis, Savivaldybe savivaldybes[])
{
    ifstream data("U2.txt");
    data >> savivaldybiuKiekis;
    for (int i = 0; i < savivaldybiuKiekis; i++)
    {
        data.ignore(21);
        char ch[14];
        data.read(ch, 13);
        ch[13] = '\0';
        savivaldybes[i].pavadinimas = ch;
        data >> savivaldybes[i].mokykluSk;
    }
    data.close();
}

// sudelioju savivaldybes i apskritis ir surandu maximus

void formatavimas(int savivaldybiuKiekis, int &apskriciuKiekis, Savivaldybe savivaldybes[], Apskritis apskritys[])
{
    for (int i = 0; i < savivaldybiuKiekis; i++)
    {
        bool canContinue = true;
        for (int j = 0; j < apskriciuKiekis; j++)
        {
            if (savivaldybes[i].pavadinimas == apskritys[j].pavadinimas)
            {
                apskritys[j].mokykluKiekiai.push_back(savivaldybes[i].mokykluSk);
                canContinue = false;
                break;
            }
        }
        if (canContinue)
        {
            apskritys[apskriciuKiekis].pavadinimas = savivaldybes[i].pavadinimas;
            apskritys[apskriciuKiekis].mokykluKiekiai.push_back(savivaldybes[i].mokykluSk);
            apskriciuKiekis++;
        }
    }

    for (int i = 0; i < apskriciuKiekis; i++)
    {
        apskritys[i].maximum = maximum(apskritys[i].mokykluKiekiai);
    }
}

void rez(int apskriciuKiekis, Apskritis apskritys[])
{
    ofstream rez("U2rez.txt");
    rez << apskriciuKiekis << endl;
    for (int i = 0; i < apskriciuKiekis; i++)
    {
        rez << apskritys[i].pavadinimas << " " << apskritys[i].mokykluKiekiai.size() << " " << apskritys[i].maximum << endl;
    }
    rez.close();
}

void sort(int apskriciuKiekis, Apskritis apskritys[])
{
    for (int i = 0; i < apskriciuKiekis; i++)
    {
        for (int j = 0; j < apskriciuKiekis - 1 - i; j++)
        {
            if (apskritys[j].maximum > apskritys[j + 1].maximum)
            {
                swap(apskritys[j], apskritys[j + 1]);
            }
            else if (apskritys[j].maximum == apskritys[j + 1].maximum && apskritys[j].pavadinimas < apskritys[j + 1].pavadinimas)
            {
                swap(apskritys[j], apskritys[j + 1]);
            }
        }
    }
}

int main()
{
    int savivaldybiuKiekis;
    int apskriciuKiekis = 0;
    Savivaldybe savivaldybes[60];
    Apskritis apskritys[60];

    skaitymas(savivaldybiuKiekis, savivaldybes);
    formatavimas(savivaldybiuKiekis, apskriciuKiekis, savivaldybes, apskritys);
    rez(apskriciuKiekis, apskritys);
    return 0;
}