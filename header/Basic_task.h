#ifndef BASIC_TASK_H
#define BASIC_TASK_H


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>

using namespace std;

class Basic_task {
protected:
 std::string *name;
 std::string *category;
 bool *completed;
};

#endif // BASIC_TASK_H