#include "../../header/user.h"

using namespace std;

void to_do_list::del(vector<string *> *cmd_record){
    int *error_flag = new int(0);

    if(cmd_record->size() < 3){
        cout << endl << "del: too few arguments..." << endl << endl;
        *error_flag = 1;
    }else if(cmd_record->size() > 3){
        cout << endl << "del: too many arguments..." << endl << endl;
        *error_flag = 1;
    }else{                  
        int *flag = new int(1);
        del((*cmd_record)[1], (*cmd_record)[2], flag);
        delete flag;
    }

    if(!(*error_flag)){
        cout << endl << "Successfully Deleted !!!" << endl << endl;
        cout << "Updated To-Do List: " << endl;
        string *type = new string("all");
        view(type);
        delete type;
    }

    delete error_flag;
}

void to_do_list::del(string *name, string *date, int *flag){

    if(!this->find_name_date(name,date)){
        cout << endl << "No such Task !!!" << endl;
    }

    vector<task*>::iterator it = (*(this->to_do)).begin();
    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            
            task *tmp  = new task(*it);
            string *op = new string("del");

            if(user_->user_op(op, user_name, name, date) && *flag == 1){
                int *n = new int(4);
                this->new_action(n, 0, tmp);  
                delete n;
            }else{
                delete tmp;
            }

            (*(this->to_do)).erase(it);

            delete op;
            
            return; 
        }
    }
    return;
}
