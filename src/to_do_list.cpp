#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "../header/to_do_list.h"

using namespace std;


to_do_list::to_do_list() : to_do(new set<task*,CompareDate>),max_name_size(6),max_category_size(10),un_re(new list<pair<int *, pair<task * , task *> > >), idx(0){}
    
int  to_do_list::find_date(string *date) const{
    if(to_do == 0){
        return 0;
    }
    set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
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
    set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            return 1;
        }
    }

    return 0;
}

void to_do_list::add(string *name,string *date, string *category, bool *completed, int flag){ //若沒有指定category就是none
    if(this->find_name_date(name, date)){//修改成date一樣, category一樣才重複
        cout << "Task already exists!" << endl;
        return;
    }

    task *tmp = new task(name,date,category, completed);
    //this->new_action
    this->to_do->insert(tmp);
    if(flag == 1)this->new_action(1, tmp, 0); //type list record
    
    max_name_size = max(max_name_size, int((*name).size()));
    max_category_size = max(max_category_size, int((*name).size()));
    // if(*category == "none"){
    //     delete category;
    // }
    return;
}

void to_do_list::edit_name(string *name, string *date, string *e){
    set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            string *ptr = (*it)->get_name();
            *ptr = *e;

            task *new_ = new task(*it);
            this->new_action(3, new_, tmp);
        }
    }
    
}

void to_do_list::edit_date(string *name, string *date, string *e){
    set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            string *ptr = (*it)->get_date();
            *ptr = *e;

            task *new_ = new task(*it);
            this->new_action(3, new_, tmp);
        }
    }
}

void to_do_list::edit_category(string *name, string *date, string *e){
    set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            string *ptr = (*it)->get_category();
            *ptr = *e;

            task *new_ = new task(*it);
            this->new_action(3, new_, tmp);
        }
    }
}

void to_do_list::edit_completed(string *name, string *date, bool *e){
    set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            bool *ptr = (*it)->get_completed();
            *ptr = *e;

            task *new_ = new task(*it);
            this->new_action(3, new_, tmp);
        }
    }
}

void to_do_list::del(string *name, string *date, int flag){
    if(!this->find_name_date(name,date)){
        cout << "No such Task !!!" << endl;
    }
    set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            
            task *tmp  = new task(*it);
            if(flag == 1)this->new_action(4, 0, tmp);
            
            (*(this->to_do)).erase(it);
            
            return; //不直接return 會出錯
        }
    }
    return;
}

void to_do_list::assign_task(task* a, task *t){
    if(a == t)return;
    *(a->get_date()) = *(t->get_date());
    *(a->get_name()) = *(t->get_name());
    *(a->get_category()) = *(t->get_category());
    *(a->get_completed()) = *(t->get_completed());
    return ;
}

void to_do_list::new_action(int type, task* ptr_list, task *ptr_record){
    pair<int *, pair<task *,task *> > *ptr = new pair<int *, pair<task *,task *> >;


    ptr->first = new int (type);
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
    //this->debug();
    idx = prev(un_re->end());

}

void to_do_list::undo(){
    if(this->un_re->empty() || idx == this->un_re->begin()){
        cout << "No Previous Action!" << endl;
        return;
    }
    auto tmp = idx;
    int *op = new int(*(tmp->first));
    task *ptr_list = tmp->second.first; //on the set
    task *ptr_record = tmp->second.second; //record

    if(*op == 1){    
        this->del(ptr_list->get_name(), ptr_list->get_date(), 0);
    }else if(*op == 3){
        this->del(ptr_list->get_name(), ptr_list->get_date(), 0);
        this->add(ptr_record->get_name(), ptr_record->get_date(), ptr_record->get_category(), ptr_record->get_completed(), 0);
    }else if(*op == 4){
        this->add(ptr_record->get_name(), ptr_record->get_date(), ptr_record->get_category(), ptr_record->get_completed(), 0);
    }
    idx--;
    cout << "Undo Operation Done!" << endl;
}

void to_do_list::redo(){
    if(this->un_re->empty() || next(idx) == this->un_re->end()){
        cout << "No Later Action!" << endl;
        return;
    }
    auto tmp = next(idx);
    int *op = (tmp->first);
    //cout << "op: " << *op << endl;
    task *ptr_list = tmp->second.first;
    task *ptr_record = tmp->second.second;
    

    if(*op == 1){    
        this->add(ptr_list->get_name(), ptr_list->get_date(), ptr_list->get_category(), ptr_list->get_completed(), 0);
    }else if(*op == 3){
        this->del(ptr_record->get_name(), ptr_record->get_date(), 0);
        this->add(ptr_list->get_name(), ptr_list->get_date(), ptr_list->get_category(), ptr_list->get_completed(), 0);
    }else if(*op == 4){
        this->del(ptr_record->get_name(), ptr_record->get_date(), 0);
    }
    ++idx;
    cout << "Redo Operation Done!" << endl;
    
}

void to_do_list::view_all_date() const{
    set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
    string *str;
    str = new string(1000, 'x');
    cout << left;
    cout << setw(15) <<"name:"  << setw(15) << "date:"  << setw(15)  << "category:" << setw(15) << "completed:" << endl;  
    for(;it != (*(this->to_do)).end();it++){               
        (*it)->view_task(max_name_size,max_category_size);
    }
    delete str;
}

void to_do_list::view_date(string *date) const{
    set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
    string *str;
    str = new string(1000, 'x');
    cout << left;
    cout << setw(15) <<"name:"  << setw(15) << "date:"  << setw(15)  << "category:" << setw(15) << "completed:" << endl;  
    for(;it != (*(this->to_do)).end();it++){   
        if(*(*it)->get_date() == *date)(*it)->view_task(max_name_size,max_category_size);
    }
    delete str;
}

to_do_list::~to_do_list(){
    auto it = this->to_do->begin();
    for(;it != this->to_do->end();it++){
        delete *it;
    }
}

void to_do_list::debug(){
    cout << "op: " ;
    list<pair<int *, pair<task* , task *> > >::iterator it = (*un_re).begin();
    it++;
    for(;it!=un_re->end();it++){
        cout << *((*it).first) << " ";
    }cout << endl;
}