#include <iostream>

using namespace std;

// skaiciuoja kiek yra skaiciu nuo 1000 iki 9999, kurie dalijasi is 3
int dalybosIs3SkaiciuKiekioRadimas()
{
    int skaiciuKiekis = 0;
    int pradinisSkaicius = 9999;
    while (pradinisSkaicius >= 1000)
    {
        pradinisSkaicius -= 3;
        skaiciuKiekis++;
    }
    return skaiciuKiekis;
}

int main()
{
    int resultatas = dalybosIs3SkaiciuKiekioRadimas();
}