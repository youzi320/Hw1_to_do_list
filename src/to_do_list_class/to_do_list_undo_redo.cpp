#include "../../header/user.h"

using namespace std;

void to_do_list::undo(vector<string *> *cmd_record){
    if(cmd_record->size() > 1){
        cout << endl << "undo: too many arguments..." << endl << endl;
    }else{                  
        if(undo()){
            cout << endl << "Undo Operation Done!" << endl;
        }
    }
}

int to_do_list::undo(){
    if(this->un_re->empty() || idx == this->un_re->begin()){
        cout << endl << "No Previous Action!" << endl;
        return 0;
    }
    list<pair<int *, pair<task* , task *> > >::iterator tmp = idx;
    int *op = new int(*(tmp->first));
    int *flag = new int(0);
    task *ptr_list = tmp->second.first; //on the set
    task *ptr_record = tmp->second.second; //record


    if(*op == 1){    
        this->del(ptr_list->get_name(), ptr_list->get_date(), flag);
    }else if(*op == 3){
        this->del(ptr_list->get_name(), ptr_list->get_date(), flag);
        this->add(ptr_record->get_name(), ptr_record->get_date(), ptr_record->get_category(), ptr_record->get_completed(), flag);
    }else if(*op == 4){
        this->add(ptr_record->get_name(), ptr_record->get_date(), ptr_record->get_category(), ptr_record->get_completed(), flag);
    }
    idx--;

    delete op;
    delete flag;
    return 1;
}

void to_do_list::redo(vector<string *> *cmd_record){
    if(cmd_record->size() > 1){
        cout << endl << "redo: too many arguments..." << endl << endl;
    }else{                  
        if(redo()){
            cout << endl << "Redo Operation Done!" << endl;
        }
    }
}


int to_do_list::redo(){
    if(this->un_re->empty() || next(idx) == this->un_re->end()){
        cout << endl << "No Later Action!" << endl;
        return 0;
    }

    list<pair<int *, pair<task* , task *> > >::iterator tmp = next(idx);
    int *op = (tmp->first);
    int *flag = new int(0);
    //cout << "op: " << *op << endl;
    task *ptr_list = tmp->second.first;
    task *ptr_record = tmp->second.second;
    
    if(*op == 1){    
        this->add(ptr_list->get_name(), ptr_list->get_date(), ptr_list->get_category(), ptr_list->get_completed(), flag);
    }else if(*op == 3){
        this->del(ptr_record->get_name(), ptr_record->get_date(), flag);
        this->add(ptr_list->get_name(), ptr_list->get_date(), ptr_list->get_category(), ptr_list->get_completed(), flag);
    }else if(*op == 4){
        this->del(ptr_record->get_name(), ptr_record->get_date(), flag);
    }
    ++idx;

    delete op;
    delete flag;
    return 1;
    
}