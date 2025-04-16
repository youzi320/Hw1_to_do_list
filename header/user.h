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
    user() : u(new set<pair<pair<string*, size_t *>, to_do_list*> *> ){}
    
    void add_user(string *name, string *password);

    pair<pair<string*, size_t *>, to_do_list*> * find_user(string *str);

    int login(string *name, string *password);
private:
    set<pair<pair<string*, size_t *>, to_do_list*> *> *u;
};

#endif

