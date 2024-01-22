#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;



void skaitymas(int& n, int& iejusiuSk, int stotiesNr[], int keleiviuSk[]){
    ifstream data("U1.txt");
    data >> n;
    int savaitesDiena;
    int keleiviai;
    int kiek_islipo;
    for(int i = 0; i<n; i++){
        data >> stotiesNr[i] >> savaitesDiena >> keleiviai >> kiek_islipo;
        keleiviuSk[i] = kiek_islipo+keleiviai;
        iejusiuSk+=keleiviai;
    }
    data.close();
}

void atrinkimas(int n, int stotiesNr[], int keleiviuSk[], int& stociuKiekis, int arrStotys[], int arrKeleiviai[]){
    int stotys[100];
    int stociuKeleiviai[100] = {0};
    int stotysCount = 0;
    for(int i = 0; i<n; i++){
        bool exists = false;
        for(int j = 0; j<stotysCount; j++){
            if(stotiesNr[i] == stotys[j]){
                stociuKeleiviai[j] += keleiviuSk[i];
                exists = true;
                break;
            }
        }
        if(!exists){
            stotys[stotysCount] = stotiesNr[i];
            stociuKeleiviai[stotysCount] = keleiviuSk[i];
            stotysCount++;
        }
    }
    stociuKiekis = stotysCount;
    for(int i = 0; i<stotysCount; i++){
        arrStotys[i] = stotys[i];
        arrKeleiviai[i] = stociuKeleiviai[i];
    }
}

void sort(int n, int stotys[], int keleiviai[]){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n-1-i; j++){
            if(stotys[j] > stotys[j+1]){
                swap(stotys[j], stotys[j+1]);
                swap(keleiviai[j], keleiviai[j+1]);
            }
        }
    }
}

// grazina didziausio nario indeksa

int maximum_i(int n, int keleiviai[]){
    int max_i = 0;
    for(int i = 0; i<n; i++){
        if(keleiviai[i] > keleiviai[max_i]){
            max_i = i;
        }
    }
    return max_i;
}


void rezStociuNumeriai(int n, int stotys[], ofstream& rez){
    for(int i = 0; i<n; i++){
        rez << setw(6) << stotys[i] << " ";
    }
    rez << endl;
}

void rezKeleiviuSkaiciai(int n, int keleiviai[], ofstream& rez){
    for(int i = 0; i<n; i++){
        rez << setw(6) << keleiviai[i] << " ";
    }
    rez << endl;
}

void rez(int n, int iejusiuSk, int daugiausiaKeleiviu, int stotys[], int keleiviai[]){
    ofstream rez("U1rez.txt");
    rezStociuNumeriai(n, stotys, rez);
    rezKeleiviuSkaiciai(n, keleiviai, rez);
    rez << setw(6) << stotys[daugiausiaKeleiviu] << endl;
    rez << setw(6) << iejusiuSk << endl;
    rez.close();
}

int main(){
    int n;
    int iejusiuSk=0;
    int stotiesNr[100];
    int keleiviuSk[100];
    skaitymas(n, iejusiuSk, stotiesNr, keleiviuSk);
    int stociuKiekis;
    int stotys[100];
    int keleiviai[100];
    atrinkimas(n, stotiesNr, keleiviuSk, stociuKiekis, stotys, keleiviai);
    sort(stociuKiekis, stotys, keleiviai);
    int daugiausiaKeleiviu = maximum_i(stociuKiekis, keleiviai);
    rez(stociuKiekis, iejusiuSk, daugiausiaKeleiviu, stotys, keleiviai);
    return 0;
}