#include "../../header/user.h"

using namespace std;


to_do_list::to_do_list() : to_do(new vector<task*>),un_re(new list<pair<int *, pair<task * , task *> > >){}
    
int to_do_list::find_date(string *date) const{
    if(to_do->empty()){
        return 0;
    }
    vector<task*>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_date() == *date){
            return 1;
        }
    }

    return 0;
}

int to_do_list::find_name_date(string *name, string *date) const{
    if(to_do == 0){
        return 0;
    }
    vector<task*>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            return 1;
        }
    }

    return 0;
}

void to_do_list::assign_task(task* a, task *t){
    if(a == t)return;
    *(a->get_date()) = *(t->get_date());
    *(a->get_name()) = *(t->get_name());
    *(a->get_category()) = *(t->get_category());
    *(a->get_completed()) = *(t->get_completed());
    return;
}

void to_do_list::new_action(int *type, task* ptr_list, task *ptr_record){
    pair<int *, pair<task *,task *> > *ptr = new pair<int *, pair<task *,task *> >;

    ptr->first = new int (*type);

    if(ptr_list == 0){
        ptr->second.first = 0;
    }else{
        ptr->second.first = new task;
        assign_task(ptr->second.first, ptr_list);
    }
    if(ptr_record == 0){
        ptr->second.second = 0;
    }else{
        ptr->second.second = new task;
        assign_task(ptr->second.second, ptr_record);
    }

    if(un_re->empty()){
        pair<int *, pair<task *,task *> > *zero = new pair<int *, pair<task *, task *> >;
        zero->first = 0;
        zero->second.first = 0;
        zero->second.second = 0;
        un_re->push_back(*zero);
    }else{
        if(idx != prev(un_re->end())){
            un_re->erase(next(idx),un_re->end());
        }
    }
    un_re->push_back(*ptr);

    idx = prev(un_re->end());

}


to_do_list::~to_do_list(){
    vector<task*>::iterator it1 = to_do->begin();
    list<pair<int *, pair<task* , task *> > >::iterator it2 = un_re->begin();

    for(;it1 != to_do->end();it1++){
        delete *it1;
    }

    for(;it2 != un_re->end();it2++){
        delete it2->first;
        delete it2->second.first;
        delete it2->second.second;
    }

    delete to_do;
    delete un_re;
}