#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "../header/task.h"
#include "../header/sort_cmp.h"

using namespace std;


bool cmp_completed_date_name(const task* c1, const task* c2){
    
    if(*(c1->get_date()) == *(c2->get_date())){
        if(*(c1->get_completed()) == *(c2->get_completed())){
            return *(c1->get_name()) < *(c2->get_name());
        }
        return *(c1->get_completed()) > *(c2->get_completed());
    }else{
        return *(c1->get_date()) < *(c2->get_date());
    }
}

bool cmp_date(const task* c1, const task* c2){
    return *(c1->get_date()) < *(c2->get_date());
}

bool cmp_name(const task* c1, const task* c2){
    return *(c1->get_name()) < *(c2->get_name());
}

bool cmp_category(const task* c1, const task* c2){
    return *(c1->get_category()) < *(c2->get_category());
}

bool cmp_complete(const task* c1, const task* c2){
    return *(c1->get_category()) < *(c2->get_category());
}