#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "../header/to_do_list.h"

using namespace std;

class user{
public:
    user() : u(new set<pair<string*, to_do_list*> *>){}
    
    void add_user(to_do_list *l);

    to_do_list* find_user(string *str);

private:
    set<pair<string*, to_do_list*> *> *u;
};

#endif

