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
    return (*y % 4 == 0 && *y % 100 != 0) || (*y % 400 == 0);
}

int check_date(string *add_date){
    
    stringstream *ss = new stringstream;
    int *y = new int;
    int *m = new int;
    int *d = new int;
    int *error_flag = new int(0);
    set<int> *m_30 = new set<int>;
    *m_30 = {2,4,6,9,11};

    char *s1 = new char, *s2 = new char;

    *ss << *add_date;
    *ss >> *y >> *s1 >> *m >> *s2 >> *d;

    if(ss->fail() || add_date->length() != 10 || *s1 != '/' || *s2 != '/'){
        *error_flag = 1;
    }else if(*y < 0 || *m < 1 || *m > 12 || *d < 1 || *d > 31){
        *error_flag = 1;
    }else if(*d == 2){
        if(!check_leap(y) && (*d > 28) ){
            *error_flag = 1;
        }else if(check_leap(y) && (*d > 29) ){
            *error_flag = 1;
        }
    }else if(m_30->count(*m)){
        if(*d > 30)*error_flag = 1;
    }

    delete ss;
    delete y;
    delete m;
    delete d;
    delete m_30;
    
    if(!(*error_flag)){
        delete error_flag;
        return 1;
    }else{
        delete error_flag;
        return 0;
    }

}