#include <iostream>
#include <fstream>
#include "DBase.h"
using namespace std;

DBase DataBase;

void readFile(char*);

int main()
{
    char fin[1000][10] = {"tphs.txt", "hlhs.txt", "kshs.txt", "tchs.txt", "tnhs.txt", "cyhs.txt", "tyhs.txt", "ylhs.txt", "pths.txt", "tths.txt"};
    int choice;
    bool hasInput = false;

    DataBase.addDept(0, 25, "Dept. of Math", 75);
    DataBase.addDept(1, 30, "Dept. of CSIE", 70);
    DataBase.addDept(2, 24, "Dept. of EE", 80);
    DataBase.addDept(3, 22, "Dept. of Phys", 75);
    DataBase.addDept(4, 20, "Dept. of Chem", 78);
    DataBase.addDept(5, 20, "Dept. of Life", 84);

    while(1){
        cout << endl << endl << endl << endl;
        cout << "\t****************************************************" << endl;
        cout << "\t*     University Admission Dispatching System      *" << endl;
        cout << "\t*     (1) Read applicant from text files           *" << endl;
        cout << "\t*     (2) Show departments' applicants             *" << endl;
        cout << "\t*     (3) Show departments' accepted applicants    *" << endl;
        cout << "\t*     (4) Show high schools' dispatching results   *" << endl;
        cout << "\t*     (0) Exit                                     *" << endl;
        cout << "\t****************************************************" << endl;
        cout << "\tInput >> ";
        cin >> choice;
        if(choice==0)
            break;
        else if(choice==1){
            for(int i=0;i<10;i++)
                readFile(fin[i]);
            DataBase.applToDept();
            hasInput = true;
            DataBase.dispatch();
            cout << "Applicant data sucessfully imported." << endl;
        }
        else if(choice>=2&&choice<=4){
            if(!hasInput){
                cout << "DataBase not ready! Perform (1) first." << endl;
                continue;
            }
            DataBase.show(choice);
        }
    }
    return 0;
}

void readFile(char* fname){
    ifstream fin;
    int school, total, ID, gender, score, wish[3];
    string name;
    fin.open(fname);
    if(!fin.is_open()){
        fin.close();
        return;
    }
    fin >> school >> total;
    for(int i=0;i<total;i++){
        fin >> name >> ID >> gender >> score;
        for(int j=0;j<3;j++)
            fin >> wish[j];
        DataBase.addData(school, name, ID, gender, score, wish[0], wish[1], wish[2]);
    }
    fin.close();
}
