#include "../../header/user.h"
#include "../../header/sort_cmp.h"

using namespace std;

void to_do_list::add(vector<string *> *cmd_record){
    int *error_flag = new int(0);
    vector<string *>::iterator cmd_it = cmd_record->begin();

    string *add_name = new string("none");
    string *add_date = new string("none");
    string *add_category = new string("none");
    bool *add_completed = new bool(false);

    if(cmd_record->size() == 1){
        cout << endl << "add: too few arguments..." << endl << endl;
        *error_flag = 1;
    }else{
        *error_flag = 0;
        cmd_it++;
        while(cmd_it != cmd_record->end()){ 

            if( (**cmd_it) == "-n" ||  (**cmd_it) == "-d" || (**cmd_it) == "-ca"){
                if (cmd_it == prev(cmd_record->end()) || (**next(cmd_it))[0] == '-') {
                    cout << endl << "add: option requires an argument -- '" << (**cmd_it)[1] << "'" << endl
                                  << "Try 'man add' for more information." << endl << endl;
                    *error_flag = 1;
                    break;
                }
                if( (**cmd_it) == "-n"){
                    *add_name = (**next(cmd_it));
                }else if( (**cmd_it) == "-d"){
                    *add_date = (**next(cmd_it));
                    if(!check_date(add_date)){
                        cout << endl << "Not a valid date format!!!" << endl
                                    << "Should be [year]/[month]/[date], ex. 2025/04/20" << endl << endl;
                        *error_flag = 1;
                    }
                }else if( (**cmd_it) == "-ca"){
                    *add_category = (**next(cmd_it));
                }
                if(cmd_it != cmd_record->end())cmd_it++;
                if(cmd_it != cmd_record->end())cmd_it++;
            }else{
                if((**cmd_it)[0] == '-'){
                    cout << endl << "add: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length())  << "'" << endl 
                                  << "Try 'man add' for more information. " << endl << endl;
                }else{
                    cout << endl << "syntax error: missing flag(s)" << endl << endl;
                }
                *error_flag = 1;
                break;
            }
        }
        
        if(!(*error_flag)){
            int *flag = new int(1);
            add(add_name, add_date, add_category, add_completed, flag);
            delete flag;
            *error_flag = 0;

            cout << endl <<  "Successfully Added !!!" << endl << endl;
        }
    }

    delete error_flag;
    delete add_name;
    delete add_date;
    delete add_category;
    delete add_completed;
}


void to_do_list::add(string *name,string *date, string *category, bool *completed, int *flag){ //若沒有指定category就是none
    if(this->find_name_date(name, date)){//修改成date一樣, category一樣才重複
        cout  << endl << "Task already exists!" << endl;
        return;
    }

    task *tmp = new task(name,date,category, completed);
    
    this->to_do->push_back(tmp);

    string *op = new string("add");
    
    sort(this->to_do->begin(), this->to_do->end(), cmp_completed_date_name);

    if(user_->user_op(op, user_name, name, date, category, completed) && *flag == 1){
        int *n = new int(1);
        this->new_action(n, tmp, 0);
        delete n;
    }

    delete op;
    return;
}
