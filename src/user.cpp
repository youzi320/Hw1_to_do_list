#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "../header/user.h"

using namespace std;

void user::add_user(to_do_list *l){
    pair<string*, to_do_list*> *ptr = new pair<string*, to_do_list*>;

    cin >> *(ptr->first);
    ptr->second = l;

    (*this->u).insert(ptr);
}

to_do_list* user::find_user(string *str){
    set<pair<string*, to_do_list*> *>::iterator it = (*this->u).begin();

    for(;it!=(*this->u).end();it++){
        if(*((*it)->first) == *str){
            return (*it)->second;
        }
    }

}