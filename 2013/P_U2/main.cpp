#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Savivaldybe{
    string pavadinimas;
    int mokykluSk = 0;
};

struct UnikaliSavivaldybe{
    string pavadinimas;
    vector<int> skaiciai;

    int maximum(){
        if(skaiciai.size()){
            return skaiciai[0];
        }
        int m = skaiciai[1];
        for(int i = 0; i<skaiciai.size(); i++){
            if(m < skaiciai[i]){
                m = skaiciai[i];
            }
        }
        return m;
    }
};

void skaitymas(vector<Savivaldybe>& savivaldybes){
    ifstream data("U2.txt");
    int n;
    data >> n;
    for(int i = 0; i<n; i++){
        data.ignore(21);
        char ch[14];
        data.read(ch, 13);
        ch[13] = '\0';
        Savivaldybe tempSavivaldybe;
        tempSavivaldybe.pavadinimas = ch;
        data >> tempSavivaldybe.mokykluSk;
        savivaldybes.push_back(tempSavivaldybe);
    }
    data.close();
}

void formatavimas(vector<Savivaldybe> savivaldybes, vector<UnikaliSavivaldybe>& unikaliosSavivaldybes){
    for(int i = 0; i<savivaldybes.size(); i++){
        bool canContinue = true;
        for(int j = 0; j<unikaliosSavivaldybes.size(); j++){
            if(savivaldybes[i].pavadinimas == unikaliosSavivaldybes[j].pavadinimas){
                unikaliosSavivaldybes[j].skaiciai.push_back(savivaldybes[i].mokykluSk);
                canContinue = false;
                break;
            }
        }
        if(canContinue){
            UnikaliSavivaldybe tempSavivaldybe;
            tempSavivaldybe.pavadinimas = savivaldybes[i].pavadinimas;
            tempSavivaldybe.skaiciai.push_back(savivaldybes[i].mokykluSk);
            unikaliosSavivaldybes.push_back(tempSavivaldybe);
        }
    }
}

void rez(vector<UnikaliSavivaldybe> unikaliosSavivaldybes){
    ofstream rez("U2rez.txt");
    rez << unikaliosSavivaldybes.size() << endl;
    for(int i = 0; i<unikaliosSavivaldybes.size(); i++){
        rez << unikaliosSavivaldybes[i].pavadinimas << " " << unikaliosSavivaldybes[i].skaiciai.size() << " " << unikaliosSavivaldybes[i].maximum() << endl;
    }
    rez.close();
}

int main(){
    vector<Savivaldybe> savivaldybes;
    skaitymas(savivaldybes);
    vector<UnikaliSavivaldybe> unikaliosSavivaldybes;
    formatavimas(savivaldybes, unikaliosSavivaldybes);
    rez(unikaliosSavivaldybes);
    return 0;
}