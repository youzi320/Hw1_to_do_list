#ifndef CHECK_H
#define CHECK_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>

using namespace std;

//檢查閏年
int check_leap(int *y);

//檢查日期是否合理
int check_date(string *add_date);

#endif