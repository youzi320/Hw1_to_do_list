#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include <cstring>
#include "../header/user.h"
#include "../header/check.h"

using namespace std;

void calendar::year(vector<string *> *cmd_record){
    if(cmd_record->size() == 1){
        cout << "year: too few arguments..." << endl << endl;
        return;
    }else if(cmd_record->size() > 2){
        cout << "year: too many arguments..." << endl << endl;
        return;
    }else{
        stringstream *ss = new stringstream;
        *ss << *(*cmd_record)[1];
        if(*ss >> *now_year){
            if(*now_year <= 0){
                cout << "Invalid Year" << endl << endl;
                *now_year = 0;
                return;
            }
        }else{
            cout << "Invalid Year" << endl << endl;
            *now_year = 0;
            return;
        }
        delete ss;
    }

    cout << "Set Year: " << *now_year << endl << endl;
    *now_month = 0;
    *now_day = 0;
}

int calendar::month(vector<string *> *cmd_record){
    if(*now_year == 0){
        cout << "Please Set Year First !!!" << endl << endl;
        return 0;
    }
    if(cmd_record->size() == 1){
        cout << "month: too few arguments..." << endl << endl;
        return 0;
    }else if(cmd_record->size() > 2){
        cout << "month: too many arguments..." << endl << endl;
        return 0;
    }else{
        stringstream *ss = new stringstream;
        *ss << *(*cmd_record)[1];
        if(*ss >> *now_month){
            if(*now_month < 1|| *now_month > 12){
                cout << "Invalid Month" << endl << endl;
                *now_month = 0;
                return 0;
            }
        }else{
            cout << "Invalid Month"<< endl << endl;
            *now_month = 0;
            return 0;
        }
        delete ss;
    }

    cout << "Set Month: " << *now_month << endl << endl;
    *now_day = 0;
    return 1;
}

int calendar::day(vector<string *> *cmd_record){

    set<int> *m_31 = new set<int>;
    set<int> *m_30 = new set<int>;
    *m_31 = {1,3,5,7,8,10,12};
    *m_30 = {4,6,9,11};
    int *d_amt = new int(0);

    if(*now_month == 2){
        if(check_leap(now_year)){
            *d_amt = 29;
        }else{
            *d_amt = 28;
        }
    }else if(m_31->count(*now_month)){
        *d_amt = 31;
    }else{
        *d_amt = 30;
    }

    if(*now_year == 0){
        cout << "Please Set Year First !!!" << endl << endl;
        return 0;
    }else if(*now_month == 0){
        cout << "Please Set Month First !!!" << endl << endl;
        return 0;
    }
    if(cmd_record->size() < 2){
        cout << "day: too few arguments..." << endl << endl;
        return 0;
    }else if(cmd_record->size() > 2){
        cout << "day: too many arguments..." << endl << endl;
        return 0;
    }else{
        stringstream *ss = new stringstream;
        *ss << *(*cmd_record)[1];
        if(*ss >> *now_day){
            if(*now_day < 1 || *now_day > *d_amt){
                cout << "Invalid Day" << endl << endl;
                *now_day = 0;
                delete ss;
                return 0;
            }
        }else{
            cout << "Invalid Day" << endl << endl;
            *now_day = 0;
            delete ss;
            return 0;
        }
        
    }

    cout << "Set Day: " << *now_day << endl << endl;
    return 1;
}
