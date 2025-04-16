#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include <cstring>
#include "../header/user.h"

using namespace std;

void calendar::year(vector<string *> *cmd_record){
    if(cmd_record->size() == 1){
        cout << "year: too few arguments..." << endl;
        return;
    }else if(cmd_record->size() > 2){
        cout << "year: too many arguments..." << endl;
        return;
    }else{
        stringstream *ss = new stringstream;
        *ss << *(*cmd_record)[1];
        if(*ss >> *now_year){
            if(*now_year <= 0){
                cout << "Invalid year" << endl;
                *now_year = 0;
                return;
            }
        }else{
            cout << "Invalid year" << endl;
            *now_year = 0;
            return;
        }
        delete ss;
    }

    cout << "Set year: " << *now_year << endl;

    
}

int calendar::month(vector<string *> *cmd_record){
    if(*now_year == 0){
        cout << "Please Set year first!!!" << endl;
        return 0;
    }
    if(cmd_record->size() == 1){
        cout << "month: too few arguments..." << endl;
        return 0;
    }else if(cmd_record->size() > 2){
        cout << "month: too many arguments..." << endl;
        return 0;
    }else{
        stringstream *ss = new stringstream;
        *ss << *(*cmd_record)[1];
        if(*ss >> *now_month){
            if(*now_month <= 0){
                cout << "Invalid month" << endl;
                *now_month = 0;
                return 0;
            }
        }else{
            cout << "Invalid month" << endl;
            *now_month = 0;
            return 0;
        }
        delete ss;
    }

    cout << "Set month: " << *now_month << endl;
    return 1;
}

