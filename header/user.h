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

extern string *user_name;


using namespace std;

class user{
public:
    user() : u(new set<pair<pair<string*, size_t *>, to_do_list*> *> ){}
    
    int add_user(string *name, string *password);

    int del_user(string *name, string *password);

    pair<pair<string*, size_t *>, to_do_list*> * find_user(string *str);
    pair<pair<string*, size_t *>, to_do_list*> * find_user(string *name, string *password);

    int login(string *name, string *password);

    int create_user_file(string *name, string *password);

    int is_user_exist(string *name);
    int is_user_exist(string *name, string *password);

    int delete_user_file(string *name, string *password);


    int user_op(string *op, string *username, string *task_name,string *date = 0, string *category = 0, bool *completed = 0, string *type = 0, string *n_str = 0);

    int load_user();

private:
    set<pair<pair<string*, size_t *>, to_do_list*> *> *u;
};

extern user *user_;

#endif

