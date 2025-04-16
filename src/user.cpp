#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include <functional>
#include "../header/user.h"

using namespace std;

void user::add_user(string *name, string *password){

    if(find_user(name) != 0){
        cout << "User already exists!!!" << endl;
        return; 
    }

    to_do_list *l = new to_do_list;
    pair<pair<string*, size_t *>, to_do_list*> *ptr = new pair<pair<string*, size_t *>, to_do_list*>;
    hash<string> str_hash;

    ptr->first.first = new string;
    ptr->first.second = new size_t;
    ptr->second = new to_do_list;

    *(ptr->first.first) = *name;
    *(ptr->first.second) = str_hash(*password);

    ptr->second = l;

    (*this->u).insert(ptr);
}

pair<pair<string*, size_t *>, to_do_list*> * user::find_user(string *str){
    set<pair<pair<string*, size_t *>, to_do_list*> *>::iterator it = (*this->u).begin();

    for(;it!=(*this->u).end();it++){
        if(*((*it)->first.first) == *str){
            return *it;
        }
    }
    return 0;
}

int user::login(string *name, string *password){
    set<pair<pair<string*, size_t *>, to_do_list*> *>::iterator it = (*this->u).begin();
    hash<string> str_hash;

    for(;it!=(*this->u).end();it++){
        if(*((*it)->first.first) == *name){
            if(*((*it)->first.second) == str_hash(*password)){
                return 1;
            }else{
                return 0;
            }
        }
    }
    return 0;
}