#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "to_do_list.h"

using namespace std;

class calendar{
public:

    calendar();

    int is_valid(vector<string *> *cmd_record, int *input, int *mn, int *mx, string *cmd);

    //calendar 模式下設定年份
    int year(vector<string *> *cmd_record);

    //calendar 模式下設定月份
    int month(vector<string *> *cmd_record);

    //calendar 模式下設定天
    int day(vector<string *> *cmd_record);

    virtual ~calendar();
    
protected:
    int *now_year;
    int *now_month;
    int *now_day;
};

#endif

