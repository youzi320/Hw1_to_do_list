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
#include "../header/sort_cmp.h"

using namespace std;

calendar::calendar(){
    now_year = new int(0);
    now_month  = new int(0);
    now_day = new int(0);
}

int calendar::is_valid(vector<string *> *cmd_record, int *input, int *mn, int *mx, string *cmd){
    if(cmd_record->size() == 1){
        cout << endl << *cmd << ": too few arguments..." << endl << endl;
        return 0;
    }else if(cmd_record->size() > 2){
        cout << endl << *cmd << ": too many arguments..." << endl << endl;
        return 0;
    }
    stringstream *ss = new stringstream;

    *ss << *(*cmd_record)[1];

    if(!(*ss >> *input) || *input < *mn || *input > *mx || (*cmd == "year" && *input < 1000)){
        cout << endl << "Invalid " << *cmd << endl << endl;
        delete ss;
        return 0;
    }

    cout << endl << "Set " << *cmd << ": " << *input << endl << endl;

    if(*cmd == "year"){
        *now_year = *input;
    }else if(*cmd == "month"){
        *now_month = *input;
    }else if(*cmd == "day"){
        *now_day = *input;
    }

    delete ss;

    return 1;
}

int calendar::year(vector<string *> *cmd_record){
    *now_month = 0;
    *now_day = 0;
    int *input = new int (0);
    int *mn = new int(0);
    int *mx = new int(1e9);
    string *s = new string("year");

    if(is_valid(cmd_record, input, mn, mx, s)){
        delete input;
        delete mn;
        delete mx;
        delete s;
        return 1;
    }else{
        delete input;
        delete mn;
        delete mx;
        delete s;
        return 0;
    }
    
}

int calendar::month(vector<string *> *cmd_record){
    if(*now_year == 0){
        cout << endl << "Please Set Year First !!!" << endl << endl;
    }
    *now_month = 0;
    *now_day = 0;
    int *input = new int (0);
    int *mn = new int(1);
    int *mx = new int(12);
    string *s = new string("month");
    
    if(is_valid(cmd_record, input, mn, mx, s)){
        delete input;
        delete mn;
        delete mx;
        delete s;

        return 1;
    }else{
        delete input;
        delete mn;
        delete mx;
        delete s;

        return 0;
    }
}

int calendar::day(vector<string *> *cmd_record){

    if(*now_year == 0){
        cout << endl << "Please Set Year First !!!" << endl << endl;
        return 0;
    }else if(*now_month == 0){
        cout << endl << "Please Set Month First !!!" << endl << endl;
        return 0;
    }

    int *input = new int(0);
    int *mn = new int(1);
    int *mx = new int(0);
    string *s = new string("day");

    set<int> *m_31 = new set<int>;
    *m_31 = {1,3,5,7,8,10,12};

    int *d_amt = new int(0);

    if(*now_month == 2){
        *d_amt = check_leap(now_year) ? 29 : 28;
    }else{
        *d_amt = m_31->count(*now_month) ? 31 : 30;
    }

    *mx = *d_amt;

    return is_valid(cmd_record, input, mn, mx, s);

    if(is_valid(cmd_record, input, mn, mx, s)){
        delete input;
        delete mn;
        delete mx;
        delete s;
        delete m_31;
        delete d_amt;

        return 1;
    }else{
        delete input;
        delete mn;
        delete mx;
        delete s;
        delete m_31;
        delete d_amt;

        return 0;
    }
       
}

calendar::~calendar(){
    delete now_year;
    delete now_month;
    delete now_day;
}