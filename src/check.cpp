#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include "../header/check.h"

using namespace std;


int check_leap(int *y){
    if(*y % 4 != 0){
        return 0;
    }else if(*y % 100 == 0 && *y % 400 != 0){
        return 0;
    }else{
        return 1;
    }
}

int check_date(string *add_date){
    stringstream *ss = new stringstream;
    int *y = new int;
    int *m = new int;
    int *d = new int;
    set<int> *m_31 = new set<int>;
    set<int> *m_30 = new set<int>;
    *m_31 = {1,3,5,7,8,10,12};
    *m_30 = {2,4,6,9,11};

    if(add_date->length() != 10){
        return 0;
    }else if(count(add_date->begin(),add_date->end(), '/') != 2 ){
        return 0;
    }else{
        replace(add_date->begin(),add_date->end(), '/', ' ');
        *ss << *add_date;
        if(*ss >> *y){
            if(*y < 0){
                return 0;
            }
        }else{
            return 0;
        }
        if(*ss >> *m){
            if(*m <=0 || *m > 12){
                return 0;
            }
        }else{  
            return 0;
        }
        if(*ss >> *d){

            if(*d < 1 || *d > 31)return 0;

            if(*d == 2){
                if(!check_leap(d) && (*d > 28) ){
                    return 0;
                }else if(check_leap(d) && (*d > 30) ){
                    return 0;
                }
            }else if(m_30->count(*m)){
                if(*d > 30)return 0;
            }
        }else{
            return 0;
        }
    }
    replace(add_date->begin(),add_date->end(), ' ', '/');
    return 1;

}