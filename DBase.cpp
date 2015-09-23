#include "DBase.h"
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

/*Member Function of applicant*/
applicant::applicant(){
    highSchool = 0;
    studName = "";
    studID = 0;
    studGender = -1;
    studScore = -1;
    studWish[0] = studWish[1] = studWish[2] = -1;
    dept = -1;
}
applicant::~applicant(){

}

void applicant::setSchool(int school){
    highSchool = school;
}
void applicant::setGender(int gender){
    studGender = gender;
}
void applicant::setName(string name){
    studName = name;
}
void applicant::setID(int id){
    studID = id;
}
void applicant::setScore(int score){
    studScore = score;
}
void applicant::setWish1(int wish){
    studWish[0] = wish;
}
void applicant::setWish2(int wish){
    studWish[1] = wish;
}
void applicant::setWish3(int wish){
    studWish[2] = wish;
}
void applicant::setDept(int Dept){
    dept = Dept;
}
int applicant::getSchool(){
    return highSchool;
}
int applicant::getGender(){
    return studGender;
}
int applicant::getID(){
    return studID;
}
string applicant::getName(){
    return studName;
}
int applicant::getScore(){
    return studScore;
}
int applicant::getWish1(){
    return studWish[0];
}
int applicant::getWish2(){
    return studWish[1];
}
int applicant::getWish3(){
    return studWish[2];
}
int applicant::getDept(){
    return dept;
}

/*Member Function of AppNode*/

void AppNode::setApp(applicant* appl){
    App = appl;
}
void AppNode::setPiority(int pio){
    piority = pio;
}
applicant* AppNode::getApp(){
    return App;
}
int AppNode::getPiority(){
    return piority;
}

/*Member Function of DBase*/

DBase::DBase(){
    dbsize = 0;
    numDept = 0;
    high[0] = "TPHS";
    high[1] = "HLHS";
    high[2] = "KSHS";
    high[3] = "TCHS";
    high[4] = "TNHS";
    high[5] = "CYHS";
    high[6] = "TYHS";
    high[7] = "YLHS";
    high[8] = "PTHS";
    high[9] = "TTHS";
}

DBase::~DBase(){
    dbsize = 0;
    numDept = 0;
}

void DBase::addData(int school, string name, int ID, int gender, int score, int wish1, int wish2, int wish3){
    applArray[dbsize].setSchool(school);
    applArray[dbsize].setName(name);
    applArray[dbsize].setID(ID);
    applArray[dbsize].setGender(gender);
    applArray[dbsize].setScore(score);
    applArray[dbsize].setWish1(wish1);
    applArray[dbsize].setWish2(wish2);
    applArray[dbsize].setWish3(wish3);
    dbsize++;
}
void DBase::addDept(int code, int capacity, string name, int threshold){
    deptArray[numDept].setCode(code);
    deptArray[numDept].setCapacity(capacity);
    deptArray[numDept].setName(name);
    deptArray[numDept].setThreshold(threshold);
    numDept++;
}
void DBase::sortAppl(int choice){
    int maxIndex;
    if(choice==1){
        for(int i=0;i<dbsize;i++){
            maxIndex = i;
            for(int j=i+1;j<dbsize;j++){
                if(applArray[j].getScore()>applArray[maxIndex].getScore())
                    maxIndex = j;
                else if(applArray[j].getScore()==applArray[maxIndex].getScore()){
                    if(applArray[j].getID()<applArray[maxIndex].getID())
                        maxIndex = j;
                }
            }
            swap(applArray[i], applArray[maxIndex]);
        }
    }
    else if(choice==2){
        for(int i=0;i<dbsize;i++){
            maxIndex = i;
            for(int j=i+1;j<dbsize;j++){
                if(applArray[j].getID()<applArray[maxIndex].getID())
                    maxIndex = j;
            }
            swap(applArray[i], applArray[maxIndex]);
        }
    }
}

void DBase::applToDept(){
    sortAppl(1);
    for(int i=0;i<dbsize;i++){
        int wish[3];
        wish[0] = applArray[i].getWish1();
        wish[1] = applArray[i].getWish2();
        wish[2] = applArray[i].getWish3();
        deptArray[wish[0]].setAppList(&applArray[i],1);
        if(wish[1]==-1)
            continue;
        deptArray[wish[1]].setAppList(&applArray[i],2);
        if(wish[2]==-1)
            continue;
        deptArray[wish[2]].setAppList(&applArray[i],3);
    }
    for(int i=0;i<NUM_DEPTS;i++)
        deptArray[i].sortAppList();
}

void DBase::dispatch(){
    applArray[0].setDept(applArray[0].getWish1());
    deptArray[applArray[0].getWish1()].setFinal(&applArray[0],1);
    for(int i=1;i<dbsize;i++){
        if(applArray[i].getScore()!=applArray[i-1].getScore()){
            for(int j=0;j<NUM_DEPTS;j++){
                if(deptArray[j].getFinalNum()>=deptArray[j].getCapacity())
                    deptArray[j].setCannotIn();
                if(deptArray[j].getThreshold()>applArray[i].getScore())
                    deptArray[j].setCannotIn();
            }
        }
        if(deptArray[applArray[i].getWish1()].getCanIn()){
            applArray[i].setDept(applArray[i].getWish1());
            deptArray[applArray[i].getWish1()].setFinal(&applArray[i],1);
        }
        else if(deptArray[applArray[i].getWish2()].getCanIn()){
            applArray[i].setDept(applArray[i].getWish2());
            deptArray[applArray[i].getWish2()].setFinal(&applArray[i],2);
        }
        else if(deptArray[applArray[i].getWish3()].getCanIn()){
            applArray[i].setDept(applArray[i].getWish3());
            deptArray[applArray[i].getWish3()].setFinal(&applArray[i],3);
        }
    }
    for(int i=0;i<NUM_DEPTS;i++)
        deptArray[i].sortFinal();
}
void DBase::show(int choice){
    if(choice==2){//department accepted
        for(int i=0;i<NUM_DEPTS;i++){
            cout << deptArray[i].getName() << endl;
            for(int j=0;j<deptArray[i].getNum();j++)
                cout << deptArray[i].getAccepted(j).getApp()->getID() << "\t(" << deptArray[i].getAccepted(j).getPiority() << ")\t[" << deptArray[i].getAccepted(j).getApp()->getScore() << "]" << endl;
            cout << endl << endl;
        }
    }
    else if(choice==3){ //department final
        for(int i=0;i<NUM_DEPTS;i++){
            int Count = 0;
            bool Show = true;
            cout << deptArray[i].getName() << "\tExpected Approval: " << deptArray[i].getCapacity() << "\t(Final Approval: " << deptArray[i].getFinalNum() << ")" << endl;
            cout << "----------------------------------------------------------------------" << endl;
            for(int j=0;j<deptArray[i].getFinalNum();j++){
                if(Show){
                    cout << Count+1 << ":";
                    Show = false;
                }
                else
                    cout << "   ";
                cout << "\t" << deptArray[i].getFinal(j).getApp()->getID() << "\t" << deptArray[i].getFinal(j).getApp()->getName();
                if(deptArray[i].getFinal(j).getApp()->getGender()==0)
                    cout << "\t(F)\t";
                else
                    cout << "\t(M)\t";
                cout << high[deptArray[i].getFinal(j).getApp()->getSchool()];
                cout << "\t[Score = " << deptArray[i].getFinal(j).getApp()->getScore();
                cout << "]\tP = " << deptArray[i].getFinal(j).getPiority() << endl;
                if(j<deptArray[i].getFinalNum()-1){
                    if(deptArray[i].getFinal(j).getApp()->getScore()!=deptArray[i].getFinal(j+1).getApp()->getScore()){
                        Count++;
                        Show = true;
                    }
                    else if(deptArray[i].getFinal(j).getPiority()<deptArray[i].getFinal(j+1).getPiority()){
                        Count++;
                        Show = true;
                    }
                }
            }
            cout << "----------------------------------------------------------------------" << endl << endl << endl;
        }
    }
    else if(choice==4){ //high school applcantion
        for(int i=0,j=0;i<NUM_HIGH;i++){
            cout << "-----------------------------------------------------------------" << endl;
            cout << high[i] << endl;
            sortAppl(2);
            for(;j<dbsize;j++){
                cout << applArray[j].getID() << "  ";
                cout << applArray[j].getName() << "\t[";
                cout << applArray[j].getScore() << "]\t";
                if(applArray[j].getDept()==-1)
                    cout << endl;
                else{
                    cout << deptArray[applArray[j].getDept()].getName() << "\t";
                    if(applArray[j].getDept()==applArray[j].getWish1())
                        cout << "<1>" << endl;
                    else if(applArray[j].getDept()==applArray[j].getWish2())
                        cout << "<2>" << endl;
                    else
                        cout << "<3>" << endl;
                }
                if(applArray[j].getSchool()!=applArray[j+1].getSchool()){
                    j++;
                    break;
                }
            }
            cout << "-----------------------------------------------------------------" << endl << endl << endl;
        }
    }
}

/*Member Function of department*/
department::department(){
    numAccepted = 0;
    numAppl = 0;
    numFinal = 0;
    canIn = true;
}
department::~department(){
    numAccepted = 0;
    numAppl = 0;
    numFinal = 0;
    canIn = true;
}

void department::setCode(int code){
    deptCode = code;
}
void department::setCapacity(int capacity){
    deptCapacity = capacity;
}
void department::setName(string name){
    deptName = name;
}
void department::setThreshold(int threshold){
    deptThreshold = threshold;
}
void department::setNum(int num){
    numAccepted = num;
}
void department::setAppList(applicant *appl,int pio){
    appList[numAppl].setApp(appl);
    appList[numAppl].setPiority(pio);
    numAppl++;
}
void department::setAccepted(AppNode appl){
    acceptedApplicants[numAccepted] = appl;
    numAccepted++;
}
void department::setFinal(applicant *appl, int pio){
    finalApp[numFinal].setApp(appl);
    finalApp[numFinal].setPiority(pio);
    numFinal++;
}
void department::setCannotIn(){
    canIn = false;
}

int department::getCode(){
    return deptCode;
}
int department::getCapacity(){
    return deptCapacity;
}
string department::getName(){
    return deptName;
}
int department::getThreshold(){
    return deptThreshold;
}
int department::getNum(){
    return numAccepted;
}
int department::getAllNum(){
    return numAppl;
}
int department::getFinalNum(){
    return numFinal;
}
bool department::getCanIn(){
    return canIn;
}
AppNode department::getAppList(int index){
    return appList[index];
}
AppNode department::getAccepted(int index){
    return acceptedApplicants[index];
}
AppNode department::getFinal(int index){
    return finalApp[index];
}
void department::sortAppList(){
    int maxIndex;
    for(int i=0;i<numAppl;i++){
        maxIndex = i;
        for(int j=i+1;j<numAppl;j++){
            if(appList[j].getApp()->getScore()>appList[maxIndex].getApp()->getScore())
                maxIndex = j;
            else if(appList[j].getApp()->getScore()==appList[maxIndex].getApp()->getScore()){
                if(appList[j].getPiority()<appList[maxIndex].getPiority())
                    maxIndex = j;
                else if(appList[j].getPiority()==appList[maxIndex].getPiority()){
                    if(appList[j].getApp()->getID()<appList[maxIndex].getApp()->getID())
                        maxIndex = j;
                }
            }
        }
        swap(appList[i], appList[maxIndex]);
        if(appList[i].getApp()->getScore()>=deptThreshold)
            setAccepted(appList[i]);
    }
}
void department::sortFinal(){
    int maxIndex;
    for(int i=0;i<numFinal;i++){
        maxIndex = i;
        for(int j=i+1;j<numFinal;j++){
            if(finalApp[j].getApp()->getScore()>finalApp[maxIndex].getApp()->getScore())
                maxIndex = j;
            else if(finalApp[j].getApp()->getScore()==finalApp[maxIndex].getApp()->getScore()){
                if(finalApp[j].getPiority()<finalApp[maxIndex].getPiority())
                    maxIndex = j;
                else if(finalApp[j].getPiority()==finalApp[maxIndex].getPiority()){
                    if(finalApp[j].getApp()->getID()<finalApp[maxIndex].getApp()->getID())
                        maxIndex = j;
                }
            }
        }
        swap(finalApp[i], finalApp[maxIndex]);
        if(finalApp[i].getApp()->getScore()>=deptThreshold)
            setAccepted(finalApp[i]);
    }
}
