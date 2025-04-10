#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "../header/task.h"


class CompareDate
{
    public:
    bool operator() (const task* c1, const task* c2) const{ //原本 &c1 &c2改成 *c1 *c2 可能出錯
        if(*(c1->get_date()) == *(c2->get_date())){
            return *(c1->get_name()) < *(c2->get_name());
        }
        return *(c1->get_date()) < *(c2->get_date());
    }
};