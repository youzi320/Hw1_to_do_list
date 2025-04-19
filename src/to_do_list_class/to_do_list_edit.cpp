
#include "../../header/user.h"

using namespace std;


void to_do_list::edit(vector<string *> *cmd_record){

    stringstream *ss;
    int *error_flag = new int(0);
    vector<string *>::iterator cmd_it = cmd_record->begin();

    string *tmp_name = new string("none");
    string *tmp_date = new string("none");
    string *tmp_category = new string("none");
    bool *tmp_completed = new bool(false);

    if(cmd_record->size() < 5){
        cout << endl << "edit: too few arguments..." << endl << endl;
        *error_flag = 1;
    }else if(cmd_record->size() > 5){
        cout << endl << "edit: too many arguments..." << endl << endl;
        *error_flag = 1;
    }else{
        *error_flag = 0;
        cmd_it =  cmd_record->begin()+3;
        if(!find_name_date((*cmd_record)[1], (*cmd_record)[2]) ){
            cout << endl << "No such Task!!!" << endl << endl;
            *error_flag = 1;
        }else if(( (**cmd_it) == "-n" || (**cmd_it) == "-d" || (**cmd_it) == "-ca" || (**cmd_it) == "-co") ){

            if((**cmd_it) == "-n"){
                *tmp_name = (**next(cmd_it));
                string *type = new string("name");
                edit((*cmd_record)[1], (*cmd_record)[2], tmp_name, type);
                delete type;
            }else if((**cmd_it) == "-d"){
                *tmp_date = (**next(cmd_it));
                if(!check_date(tmp_date)){
                    cout << endl <<  "Not a valid date format!!!" << endl
                                << "Should be [year]/[month]/[date], ex. 2025/04/20" << endl << endl;
                    *error_flag = 1;
                }else{
                    string *type = new string("date");
                    edit((*cmd_record)[1], (*cmd_record)[2], tmp_date, type);
                    delete type;
                }
                
            }else if((**cmd_it) == "-ca"){
                *tmp_category = (**next(cmd_it));

                string *type = new string("category");
                edit((*cmd_record)[1], (*cmd_record)[2], tmp_category, type);
                delete type;
            }else if((**cmd_it) == "-co"){
                if(**next(cmd_it) != "0" && **next(cmd_it) != "1"){
                    cout << endl << "edit: syntax error near unexpected token " << **next(cmd_it) << endl << endl;
                    *error_flag = 1;
                }else{
                    ss = new stringstream;
                    *ss << (**next(cmd_it));
                    *ss >> *tmp_completed;

                    string *type = new string("completed");
                    string *b_str = new string(to_string(*tmp_completed));
                    edit((*cmd_record)[1], (*cmd_record)[2],  b_str,type);

                    delete type;
                    delete b_str;
                    delete ss;
                }  
            }
        }else{
            if((**cmd_it)[0] == '-'){
                cout << endl << "edit: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length())  << "'" << endl 
                            << "Try 'man edit' for more information. " << endl << endl;
            }else{
                cout << "edit: syntax error missing flag(s)" << endl << endl;
            }
            *error_flag = 1;
        }
    }

    if(!(*error_flag)){
        cout << endl << "Successfully Edited !!!" << endl << endl;
        cout << "Updated To-Do List: " << endl;
        string *type = new string("all");
        view(type);
        delete type;
    }

    delete error_flag;
    delete tmp_name;
    delete tmp_date;
    delete tmp_category;
    delete tmp_completed;
}


void to_do_list::edit(string *name, string *date, string *str, string *type){
    vector<task*>::iterator it = (*(this->to_do)).begin();
    string *ptr;
    bool *b_ptr;
    string *op = new string("edit");

    for(;it != (*(this->to_do)).end();it++){
        if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
            task *tmp  = new task(*it);

            if(*type == "name"){
                ptr = (*it)->get_name();
                *ptr = *str;
            }else if(*type == "date"){
                ptr = (*it)->get_date();
                *ptr = *str;
            }else if(*type == "category"){
                ptr = (*it)->get_category();
                *ptr = *str;
            }else if(*type == "completed"){
                b_ptr = (*it)->get_completed();
                if(str != 0){ //str為pointer
                    if(*str == "0"){
                        *b_ptr = false;
                    }else if(*str == "1"){
                        *b_ptr = true;
                    }
                }else{
                    *b_ptr = !(*b_ptr);
                    str = new string;
                    *str = to_string(*b_ptr);
                }
            }
            
            task *new_ = new task(*it);

            int *n = new int(3);
            this->new_action(n, new_, tmp);
            delete n;

            user_->user_op(op, user_name, name, date, 0, 0, type, str);

            
        }
    }

    delete op;
}