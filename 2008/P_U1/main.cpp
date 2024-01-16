#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

void skaitymas(int& n, int& iejusiuSk, int stotiesNr[], int keleiviuSk[]){
    ifstream data("U1.txt");
    data >> n;
    int temp;
    int keleiviai;
    for(int i = 0; i<n; i++){
        data >> stotiesNr[i] >> temp >> keleiviai >> temp;
        keleiviuSk[i] = temp+keleiviai;
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
            stociuKeleiviai[stotysCount] += keleiviuSk[i];
            stotysCount++;
        }
    }
    stociuKiekis = stotysCount;
    for(int i = 0; i<stotysCount; i++){
        arrStotys[i] = stotys[i];
        arrKeleiviai[i] = stociuKeleiviai[i];
        //cout << stotys[i] << " " << stociuKeleiviai[i] << endl;
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

int maximum(int n, int keleiviai[]){
    int max_i = 0;
    for(int i = 0; i<n; i++){
        if(keleiviai[i] > keleiviai[max_i]){
            max_i = i;
        }
    }
    return max_i;
}

void rez(int n, int iejusiuSk, int daugiausiaKeleiviu, int stotys[], int keleiviai[]){
    ofstream rez("U1rez.txt");
    for(int i = 0; i<n; i++){
        rez << setw(4) << stotys[i] << " ";
    }
    rez << endl;
    for(int i = 0; i<n; i++){
        rez << setw(4) << keleiviai[i] << " ";
    }
    rez << endl;
    rez << setw(4) << stotys[daugiausiaKeleiviu] << endl;
    rez << setw(4) << iejusiuSk << endl;
}

int main(){
    int n;
    int iejusiuSk=0;
    int stotiesNr[100];
    int keleiviuSk[100];
    skaitymas(n, iejusiuSk, stotiesNr, keleiviuSk);
    //cout << iejusiuSk << endl;
    // for(int i = 0; i<n; i++){
    //     cout << stotiesNr[i] << " " << keleiviuSk[i] << endl;
    // }
    int stociuKiekis;
    int stotys[100];
    int keleiviai[100];
    atrinkimas(n, stotiesNr, keleiviuSk, stociuKiekis, stotys, keleiviai);
    sort(stociuKiekis, stotys, keleiviai);
    int daugiausiaKeleiviu = maximum(stociuKiekis, keleiviai);
    // for(int i = 0; i<stociuKiekis; i++){
    //     cout << stotys[i] << " " << keleiviai[i] << endl;
    // }
    // cout << stotys[daugiausiaKeleiviu] << endl;
    rez(stociuKiekis, iejusiuSk, daugiausiaKeleiviu, stotys, keleiviai);
}