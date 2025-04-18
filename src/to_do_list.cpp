#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <fstream>
#include "../header/to_do_list.h"
#include "../header/sort_cmp.h"
#include "../header/check.h"
#include "../header/user.h"

using namespace std;


to_do_list::to_do_list() : to_do(new vector<task*>),max_name_size(6),max_category_size(10),un_re(new list<pair<int *, pair<task * , task *> > >), idx(0){}
    
int  to_do_list::find_date(string *date) const{
    if(to_do == 0){
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

void to_do_list::add(string *name,string *date, string *category, bool *completed, int flag){ //若沒有指定category就是none
    if(this->find_name_date(name, date)){//修改成date一樣, category一樣才重複
        cout  << endl << "Task already exists!" << endl;
        return;
    }


    task *tmp = new task(name,date,category, completed);
    //this->new_action
    this->to_do->push_back(tmp);

    // cout << *( (*this->to_do)[0]->get_name()) << endl;
    
    max_name_size = max(max_name_size, int((*name).size()));
    max_category_size = max(max_category_size, int((*name).size()));
    // if(*category == "none"){
    //     delete category;
    // }
    string *op = new string("add");
    
    sort(this->to_do->begin(), this->to_do->end(), cmp_completed_date_name);


    if(user_->user_op(op, user_name, name, date, category, completed) && flag == 1){
        this->new_action(1, tmp, 0);
    }

    delete op;
    return;
}

void to_do_list::edit_name(string *name, string *date, string *e){
    vector<task*>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            string *ptr = (*it)->get_name();
            *ptr = *e;

            task *new_ = new task(*it);
            this->new_action(3, new_, tmp);

            string *op = new string("edit");
            string *type = new string("name");
            user_->user_op(op, user_name, name, date, 0, 0, type, e);
        }
    }
    
}

void to_do_list::edit_date(string *name, string *date, string *e){
    vector<task*>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            string *ptr = (*it)->get_date();
            *ptr = *e;

            task *new_ = new task(*it);
            this->new_action(3, new_, tmp);

            string *op = new string("edit");
            string *type = new string("date");
            user_->user_op(op, user_name, name, date, 0, 0, type, e);
        }
    }
}

void to_do_list::edit_category(string *name, string *date, string *e){
    vector<task*>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            string *ptr = (*it)->get_category();
            *ptr = *e;

            task *new_ = new task(*it);
            this->new_action(3, new_, tmp);

            string *op = new string("edit");
            string *type = new string("category");
            user_->user_op(op, user_name, name, date, 0, 0, type, e);
        }
    }
}

void to_do_list::edit_completed(string *name, string *date, bool *e){
    vector<task*>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            bool *ptr = (*it)->get_completed();
            *ptr = *e;

            task *new_ = new task(*it);
            this->new_action(3, new_, tmp);

            string *op = new string("edit");
            string *type = new string("completed");
            string *b_str = new string(to_string(*e));
            user_->user_op(op, user_name, name, date, 0, 0, type, b_str);
        }
    }
}

void to_do_list::edit_completed(string *name, string *date){
    vector<task*>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            bool *ptr = (*it)->get_completed();
            *ptr = !(*ptr);

            task *new_ = new task(*it);
            this->new_action(3, new_, tmp);

            string *op = new string("edit");
            string *type = new string("completed");
            string *b_str = new string(to_string(!(*ptr)));
            user_->user_op(op, user_name, name, date, 0, 0, type, b_str);
        }
    }
}

void to_do_list::del(string *name, string *date, int flag){
    if(!this->find_name_date(name,date)){
        cout << "No such Task !!!" << endl;
    }
    vector<task*>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            
            task *tmp  = new task(*it);
            string *op = new string("del");

            if(user_->user_op(op, user_name, name, date) && flag == 1){
                if(flag == 1)this->new_action(4, 0, tmp);  
            }

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

int to_do_list::undo(){
    if(this->un_re->empty() || idx == this->un_re->begin()){
        cout << "No Previous Action!" << endl;
        return 0;
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
    return 1;
}

int to_do_list::redo(){
    if(this->un_re->empty() || next(idx) == this->un_re->end()){
        cout << "No Later Action!" << endl;
        return 0;
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
    return 1;
    
}

void to_do_list::view_all_date() const{
    vector<task*>::iterator it = (*(this->to_do)).begin();
    string *str;

    int *flag = new int(0);

    str = new string(1000, 'x');
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout <<"| name:"  << setw(21) << "| date:"  << setw(25)  << "| category:" << setw(32) << "| completed:         |" << endl;  
    cout << "-------------------------------------------------------------------------------------" << endl;

    for(;it != (*(this->to_do)).end();it++){               
        (*it)->view_task(max_name_size,max_category_size);
        *flag = 1;
    }

    if(*flag == 0){
        cout << "!!!" << setw(44) << "No Task Yet" << setw(38) << "!!!" << endl << endl;
    }

    delete str;
    cout << right;
}

void to_do_list::view_date(string *date) const{
    vector<task*>::iterator it = (*(this->to_do)).begin();
    string *str;
    int *flag = new int(0);

    str = new string(1000, 'x');
    str = new string(1000, 'x');
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout <<"| name:"  << setw(21) << "| date:"  << setw(25)  << "| category:" << setw(32) << "| completed:         |" << endl; 
    cout << "-------------------------------------------------------------------------------------" << endl;
    for(;it != (*(this->to_do)).end();it++){   
        if(*(*it)->get_date() == *date)(*it)->view_task(max_name_size,max_category_size);
        *flag = 1;
    }

    if(*flag == 0){
        cout << "!!!" << setw(44) << "No Task Yet" << setw(38) << "!!!" << endl << endl;
    }

    delete str;

    cout << right;
}

void to_do_list::view_done() const{
    vector<task*>::iterator it = (*(this->to_do)).begin();
    string *str;
    int *flag  = new int(0);

    str = new string(1000, 'x');
    str = new string(1000, 'x');
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout <<"| name:"  << setw(21) << "| date:"  << setw(25)  << "| category:" << setw(32) << "| completed:         |" << endl; 
    cout << "-------------------------------------------------------------------------------------" << endl;
    for(;it != (*(this->to_do)).end();it++){   
        if(*(*it)->get_completed() == true){
            (*it)->view_task(max_name_size,max_category_size);
            *flag = 1;
        }
    }

    if(*flag == 0){
        cout << "!!!" << setw(44) << "No Task Yet" << setw(38) << "!!!" << endl << endl;
    }

    delete str;

    cout << right;
}

void to_do_list::view_undone() const{
    vector<task*>::iterator it = (*(this->to_do)).begin();
    string *str;
    int *flag = new int(0);

    str = new string(1000, 'x');
    str = new string(1000, 'x');
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout <<"| name:"  << setw(21) << "| date:"  << setw(25)  << "| category:" << setw(32) << "| completed:         |" << endl; 
    cout << "-------------------------------------------------------------------------------------" << endl;
    for(;it != (*(this->to_do)).end();it++){   
        if(*(*it)->get_completed() == false){
            (*it)->view_task(max_name_size,max_category_size);
            *flag = 1;
        }
    }

    if(*flag == 0){
        cout << "!!!" << setw(44) << "No Task Yet" << setw(38) << "!!!" << endl << endl;
    }

    delete str;

    cout << right;
}

void to_do_list::print_month(int *m){
    // set<task*> *same_month = new set<task*>;
    // for(auto i: *to_do){
    //     string *tmp = i->get_date();
    //     if( stoi(tmp->substr(tmp->find('/'), 2)) == *m ){
    //         same_month->insert(i); 
    //     }
    // }

    set<int> *m_31 = new set<int>;
    set<int> *m_30 = new set<int>;
    *m_31 = {1,3,5,7,8,10,12};
    *m_30 = {4,6,9,11};
    int *d_amt = new int(0);

    if(*m == 2){
        if(check_leap(now_year)){
            *d_amt = 29;
        }else{
            *d_amt = 28;
        }
    }else if(m_31->count(*m)){
        *d_amt = 31;
    }else{
        *d_amt = 30;
    }

    struct tm *time = new struct tm;

    memset(time, 0, sizeof(*time));

    time->tm_mday = 1;
    time->tm_mon = *m - 1;
    time->tm_year = *now_year-1900;

    mktime(time);

    cout << right;
    cout << "Year: " << *now_year << endl;

    for(int j=0;j<22*7 + 1;j++){
        cout << "-";
    }cout << endl;
    cout << "|" ;
    cout << setw(12) << "Sun" << setw(10) << "|";
    cout << setw(12) << "Mon" << setw(10) << "|";
    cout << setw(12) << "Tue" << setw(10) << "|";
    cout << setw(12) << "Wed" << setw(10) << "|";
    cout << setw(12) << "Thu" << setw(10) << "|";
    cout << setw(12) << "Fri" << setw(10) << "|";
    cout << setw(12) << "Sat" << setw(10) << "|";
    cout << endl;

    for(int j=0;j<22*7 + 1;j++){
        cout << "-";
    }cout << endl;

    //int *i = new int;
    int *flag = new int(0);
    string *space = new string("                     ");
    //int *j = new int;
    int *p_day = new int(1);
    pair< pair< vector<task*>::iterator, vector<task*>::iterator>,  vector<task*>::iterator> **date_task;
    date_task = new pair< pair< vector<task*>::iterator, vector<task*>::iterator>,  vector<task*>::iterator> *[7];

    for(int i=0;i<7;i++){
        date_task[i] = new pair< pair< vector<task*>::iterator, vector<task*>::iterator>,  vector<task*>::iterator>;
    }


    while(*p_day <= *d_amt){
        cout << "|";
        for(int j=0;j<7;j++){
            if(*p_day <= *d_amt && (j == time->tm_wday || *flag == 1)){
                *flag = 1;
                string *pt_month = new string(to_string(*m));
                string *pt_day = new string(to_string(*p_day));
                string *pt_date = new string;

                if(*m < 10){
                    *pt_month = "0" + to_string(*m);
                }
                if(*p_day < 10){
                    *pt_day = "0" + to_string(*p_day);

                }
                (*p_day)++;

                *pt_date = *pt_month + "/" + *pt_day;
                
                cout << setw(13) << *pt_date;
                cout << setw(9) << "|";

                *pt_date = to_string(*now_year) + "/" + *pt_date;

                task *tmp = new task(pt_date);
                
                sort(to_do->begin(), to_do->end(), cmp_date);
                date_task[j]->first.first = lower_bound(to_do->begin(), to_do->end(), tmp, cmp_date);
                date_task[j]->first.second = upper_bound(to_do->begin(), to_do->end(), tmp, cmp_date);
                date_task[j]->second = date_task[j]->first.first;
                sort(to_do->begin(), to_do->end(), cmp_completed_date_name);

            }else{
                cout << *space << "|";
            }
            
        }cout << endl;

        for(int j=0;j<22*7 + 1;j++){
            cout << "-";
        }cout << endl;

        //for一大格為一天(一大格j小格)
        for(int j=0;j<6;j++){//每天格數
            cout << "|";
            for(int k=0;k<7;k++){//七天各跑一遍
                //條件待檢查
                if(date_task[k]->first.first != date_task[k]->first.second  &&  date_task[k]->second != prev(date_task[k]->first.second) && date_task[k]->second != date_task[k]->first.second && j == 5){
                    cout << setw(21) << "..." << "|";
                }else if((date_task[k]->first.first != date_task[k]->first.second) && date_task[k]->second != date_task[k]->first.second){
                    cout << setw(18) << *((*date_task[k]->second)->get_name());
                    if( *((*date_task[k]->second)->get_completed()) ){
                        cout << "(x)";
                    }else{
                        cout << "( )";
                    }
                    cout << "|";
                    if(date_task[k]->second != date_task[k]->first.second)(date_task[k]->second)++;
                }else{
                    cout << *space << "|";
                }

            }cout << endl;
        }
       for(int j=0;j<22*7 + 1;j++){
            cout << "-";
        }cout << endl;

    }
    

}

void to_do_list::print_day(int *d){
    string *pt_month = new string(to_string(*now_month));
    string *pt_day = new string(to_string(*now_day));
    string *pt_date = new string;

    
    
    cout << "Year: " << *now_year << endl;

    sort(to_do->begin(), to_do->end(), cmp_date);
    
   
    if(*now_month < 10){
        *pt_month = "0" + to_string(*now_month);
    }
    if(*now_day < 10){
        *pt_day = "0" + to_string(*now_day);

    }
    
    
    *pt_date = *pt_month + "/" + *pt_day;


    for(int i=0;i<21 + 2;i++){
        cout << "-";
    }cout << endl;

    cout << "|";
    cout << setw(13) << *pt_date << setw(9) << "|" << endl;


    *pt_date = to_string(*now_year) + "/" + *pt_date;

    task *tmp = new task(pt_date);
    vector<task *>::iterator low_it = lower_bound(to_do->begin(), to_do->end(), tmp, cmp_date);
    vector<task *>::iterator up_it = upper_bound(to_do->begin(), to_do->end(), tmp, cmp_date);
    vector<task *>::iterator it = low_it;

    
   

    for(int i=0;i<21 + 2;i++){
        cout << "-";
    }cout << endl;

    if(it == up_it){
        cout << "!!!" << setw(14) << "No Task Yet" << setw(6) << "!!!" << endl << endl;
    }else{
        while(it != up_it){
            cout << "|";

            cout << setw(18) << *((*it)->get_name());

            if(*((*it)->get_completed())){
                cout << "(x)";
            }else{
                cout << "( )";
            }

            cout << "|" << endl;
            
            it++;
        }
        for(int i=0;i<21 + 2;i++){
            cout << "-";
        }cout << endl;
    }    
    

    sort(to_do->begin(), to_do->end(), cmp_completed_date_name);
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

