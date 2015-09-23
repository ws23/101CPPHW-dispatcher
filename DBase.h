#include <iostream>
#define NUM 50000
#define NUM_DEPTS 6
#define NUM_HIGH 10
using std::string;

class applicant{
    private:
        int highSchool;
        int studGender; // 0-Female 1-Male
        int studID;
        string studName;
        int studScore;
        int studWish[3];
        int dept;
        int piority;
    public:
        applicant();
        ~applicant();
        void setSchool(int);
        void setName(string);
        void setID(int);
        void setGender(int);
        void setScore(int);
        void setWish1(int);
        void setWish2(int);
        void setWish3(int);
        void setDept(int);
        int getSchool();
        int getGender();
        int getID();
        string getName();
        int getScore();
        int getWish1();
        int getWish2();
        int getWish3();
        int getDept();
};

class AppNode{
    private:
        applicant *App;
        int piority;
    public:
        void setApp(applicant*);
        void setPiority(int);
        applicant* getApp();
        int getPiority();

};

class department{
    private:
        int deptCode; // math=0, csie=1, ee=2, phy=3, chem=4, life=5
        int deptCapacity;
        string deptName;
        int deptThreshold;
        int numAccepted;
        int numAppl;
        int numFinal;
        bool canIn;
        AppNode acceptedApplicants[NUM];
        AppNode appList[NUM];
        AppNode finalApp[NUM];
    public:
        department();
        ~department();
        void setCode(int);
        void setCapacity(int);
        void setName(string);
        void setThreshold(int);
        void setNum(int);
        void setAppList(applicant*, int);
        void setAccepted(AppNode);
        void setFinal(applicant*, int);
        void setCannotIn();
        void sortAppList();
        void sortFinal();
        int getCode();
        int getCapacity();
        string getName();
        int getThreshold();
        int getNum();
        int getAllNum();
        int getFinalNum();
        bool getCanIn();
        AppNode getAppList(int);
        AppNode getAccepted(int);
        AppNode getFinal(int);
};

class DBase{
    private:
        applicant applArray[NUM];
        int dbsize;
        int numDept;
        string high[10];
    public:
        DBase();
        ~DBase();
        department deptArray[NUM_DEPTS];
        void addData(int, string, int, int, int, int, int, int);
        void addDept(int, int, string, int);
        void sortAppl(int);
        void applToDept();
        void dispatch();
        void show(int);
};
