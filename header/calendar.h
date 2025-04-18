#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "../header/to_do_list.h"

using namespace std;

class calendar{
public:

    calendar(){
        now_year = new int(0);
        now_month  = new int(0);
        now_day = new int(0);
    }

    void year(vector<string *> *cmd_record);
    int month(vector<string *> *cmd_record);
    int day(vector<string *> *cmd_record);
    
protected:
    int *now_year;
    int *now_month;
    int *now_day;
};

#endif

