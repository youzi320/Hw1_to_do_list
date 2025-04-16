#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include "../header/to_do_list.h"

using namespace std;

int to_do_list::check_leap(int *y){
    if(*y % 4 != 0){
        return 0;
    }else if(*y % 100 == 0 && *y % 400 != 0){
        return 0;
    }else{
        return 1;
    }
}

int to_do_list::check_date(string *add_date){
    stringstream *ss = new stringstream;
    int *y = new int;
    int *m = new int;
    int *d = new int;
    set<int> *m_31 = new set<int>;
    set<int> *m_30 = new set<int>;
    *m_31 = {1,3,5,7,8,10,12};
    *m_30 = {2,4,6,9,11};

    if(count(add_date->begin(),add_date->end(), '/') != 2 ){
        return 0;
    }else{
        replace(add_date->begin(),add_date->end(), '/', ' ');
        *ss << *add_date;
        if(*ss >> *y){
            if(*y < 0){
                return 0;
            }
        }else{
            return 0;
        }
        if(*ss >> *m){
            if(*m <=0 || *m > 12){
                return 0;
            }
        }else{  
            return 0;
        }
        if(*ss >> *d){

            if(*d < 1 || *d > 31)return 0;

            if(*d == 2){
                if(!check_leap(d) && (*d > 28) ){
                    return 0;
                }else if(check_leap(d) && (*d > 30) ){
                    return 0;
                }
            }else if(m_30->count(*m)){
                if(*d > 30)return 0;
            }
        }else{
            return 0;
        }
    }
    replace(add_date->begin(),add_date->end(), ' ', '/');
    return 1;

}

void to_do_list::add(vector<string *> *cmd_record){
    int *error_flag = new int;
    auto cmd_it = cmd_record->begin();

    string *add_name = new string(1000,'x');
    string *add_date = new string(15,'x');
    string *add_category = new string(1000,'x');
    bool *add_completed = new bool(false);

    *add_name = "none";
    *add_date = "none";
    *add_category = "none";

    if(cmd_record->size() == 1){
        cout << "add: too few arguments..." << endl;

    }else{
        *error_flag = 0;
        cmd_it++;
        while(cmd_it != cmd_record->end()){ 

            if( (**cmd_it) == "-n" ||  (**cmd_it) == "-d" || (**cmd_it) == "-ca"){
                if (cmd_it == prev(cmd_record->end()) || (**next(cmd_it))[0] == '-') {
                    cout << "add: option requires an argument -- '" << (**cmd_it)[1] << "'" << endl
                        << "Try 'man add' for more information." << endl;
                    *error_flag = 1;
                    break;
                }
                if( (**cmd_it) == "-n"){
                    *add_name = (**next(cmd_it));
                }else if( (**cmd_it) == "-d"){
                    *add_date = (**next(cmd_it));
                    if(!check_date(add_date)){
                        cout <<  "Not a valid date format!!!" << endl;
                        cout << "Should be [year]/[month]/[date], ex. 2025/04/20" << endl;
                        *error_flag = 1;
                    }
                }else if( (**cmd_it) == "-ca"){
                    *add_category = (**next(cmd_it));
                }
                if(cmd_it != cmd_record->end())cmd_it++;
                if(cmd_it != cmd_record->end())cmd_it++;
            }else{
                if((**cmd_it)[0] == '-'){
                    cout << "add: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length())  << "'" << endl 
                        << "Try 'man add' for more information. " << endl;
                }else{
                    cout << "syntax error: missing flag(s)" << endl;
                }
                *error_flag = 1;
                break;
            }
        }
        
        if(!(*error_flag)){
            add(add_name, add_date, add_category, add_completed);
            
            *error_flag = 0;
            
            add_name = new string(1000,'x');
            add_date = new string(15,'x');
            add_category = new string(1000,'x');
            add_completed = new bool(false);

            *add_name = "none";
            *add_date = "none";
            *add_category = "none";
        }
    }

    delete error_flag;
    delete add_name;
    delete add_date;
    delete add_category;
    delete add_completed;

}

void to_do_list::view(vector<string *> *cmd_record){

    auto cmd_it = cmd_record->begin();
    if(cmd_record->size() == 1){
        //預設全輸出
        view_all_date();
    }else if(cmd_record->size() > 3){
        cout << "view: too many arguments" << endl;
    }else{
        cmd_it++;
        if(**cmd_it == "-a" || **cmd_it == "-m" || **cmd_it == "-ca"){

            if( **cmd_it == "-a" ){
                view_all_date();
            }else{
                if(cmd_record->size() < 3){
                    cout << "view: too few arguments" << endl;
                }else if ((**next(cmd_it))[0] == '-') {
                    cout << "view: option requires an argument -- '" << (**cmd_it)[1] << endl
                            << "Try 'man view' for more information." << endl;
                }

                if( **cmd_it == "-d" ){
                    view_date(*next(cmd_it));
                }else if( **cmd_it== "-ca" ){
                    if ((**next(cmd_it))[0] == '-') {
                        cout << "view: option requires an argument -- '" << (**cmd_it)[1] << endl
                            << "Try 'man view' for more information." << endl;
                    }else{
                        //輸出(To-Do)
                    }
                }
            }
        }else{
            if((**cmd_it)[0] == '-'){
                cout << "view: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length()) << endl 
                    << "' Try 'man view' for more information. " << endl;
            }
        }
    }
}

void to_do_list::edit(vector<string *> *cmd_record){

    stringstream *ss;
    int *error_flag = new int;
    auto cmd_it = cmd_record->begin();

    string *tmp_name = new string(1000,'x');
    string *tmp_date = new string(15,'x');
    string *tmp_category = new string(1000,'x');
    bool *tmp_completed = new bool(false);

    *tmp_name = "none";
    *tmp_date = "none";
    *tmp_category = "none";

    if(cmd_record->size() < 5){
        cout << "edit: too few arguments..." << endl;

    }else if(cmd_record->size() > 5){
        cout << "edit: too many arguments..." << endl;
    }else{
        *error_flag = 0;
        cmd_it =  cmd_record->begin()+3;
        if(!find_name_date((*cmd_record)[1], (*cmd_record)[2]) ){
            cout << "No such Task!!!" << endl;
        }else if(( (**cmd_it) == "-n" || (**cmd_it) == "-d" || (**cmd_it) == "-ca" || (**cmd_it) == "-co") ){

            if((**cmd_it) == "-n"){
                *tmp_name = (**next(cmd_it));
                edit_name((*cmd_record)[1], (*cmd_record)[2], tmp_name);
            }else if((**cmd_it) == "-d"){
                *tmp_date = (**next(cmd_it));
                edit_date((*cmd_record)[1], (*cmd_record)[2], tmp_date);
            }else if((**cmd_it) == "-ca"){
                *tmp_category = (**next(cmd_it));
                edit_category((*cmd_record)[1], (*cmd_record)[2], tmp_category);
            }else if((**cmd_it) == "-co"){
                if(**next(cmd_it) != "0" && **next(cmd_it) != "1"){
                    cout << "edit: syntax error near unexpected token " << **next(cmd_it) << endl;
                    *error_flag = 1;
                }else{
                    ss = new stringstream;
                    *ss << (**next(cmd_it));
                    *ss >> *tmp_completed;
                    edit_completed((*cmd_record)[1], (*cmd_record)[2], tmp_completed);
                    delete ss;
                }  
            }
        }else{
            if((**cmd_it)[0] == '-'){
                cout << "edit: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length())  << "'" << endl 
                    << "Try 'man edit' for more information. " << endl;
            }else{
                cout << "edit: syntax error missing flag(s)" << endl;
            }
            *error_flag = 1;
        }
    }

    delete error_flag;
    delete tmp_name;
    delete tmp_date;
    delete tmp_category;
    delete tmp_completed;
}



void to_do_list::man (int *op){
    if(*op == 0){
        cout << "add task(1)" << endl;
        cout << "view task(2)" << endl;
        cout << "edit task(3)" << endl;
        cout << "delete task(4)" << endl;
        cout << "undo(5) redo(6)" << endl;
    }else if(*op == 1){
        cout << "Usage: add [-n] [-d] [-ca]" << endl;
        cout << "-n\tname" << endl;
        cout << "-d\tdate\tFormat:[year]/[month]/[date], ex. 2025/04/20" << endl;
        cout << "-c\tcategory" << endl;
    }else if(*op == 2){
        cout << "Usage: view [-a] [-m] [-ca]" << endl;
        cout << "-a\tview all task" << endl;
        cout << "-d\tview by specific date" << endl;
        cout << "-c\tview by category" << endl;
    }else if(*op == 3){
        cout << "Usage: edit [original name] [orginal date] [-n] [-d] [-ca] [-co] " << endl;
        cout << "-n\tedit name" << endl;
        cout << "-d\tedit date" << endl;
        cout << "-ca\tedit category" << endl;
        cout << "-co\trdit completed" << endl;
    }else if(*op == 4){
        cout << "Usage: delete [name] [date]" << endl;
    }
    
}

void to_do_list::del(vector<string *> *cmd_record){
    if(cmd_record->size() < 3){
        cout << "del: too few arguments..." << endl;

    }else if(cmd_record->size() > 3){
        cout << "del: too many arguments..." << endl;
    }else{                  
        del((*cmd_record)[1], (*cmd_record)[2]);
    }
}

void to_do_list::undo(vector<string *> *cmd_record){
    if(cmd_record->size() > 1){
        cout << "undo: too many arguments..." << endl;
    }else{                  
        undo();
    }
}

void to_do_list::redo(vector<string *> *cmd_record){
    if(cmd_record->size() > 1){
        cout << "redo: too many arguments..." << endl;

    }else{                  
        redo();
    }
}

void to_do_list::man(vector<string *> *cmd_record){
    int *tmp_int = new int;

    if(cmd_record->size() < 2){
        cout << "man: too few arguments..." << endl;

    }else if(cmd_record->size() > 2){
        cout << "man: too many arguments..." << endl;
    }else{                  
        if(*(*cmd_record)[1] == "add"){
            *tmp_int = 1;
        }else if(*(*cmd_record)[1] == "view"){
            *tmp_int = 2;
        }else if(*(*cmd_record)[1] == "edit"){
            *tmp_int = 3;
        }else if(*(*cmd_record)[1] == "del"){
            *tmp_int = 4;
        }
        man(tmp_int);
    }

    delete tmp_int;
}

void to_do_list::calendar(vector<string *> *cmd_pre){
    if(cmd_pre != 0 && cmd_pre->size() > 1){
        cout << "calendar: too few arguments..." << endl;
    }else{

        int *y = new int(0);
        int *m = new int(0);
        int *w_day = new int(0);

        string *cmd = new string(1000,'\0');
        string *cmd_tmp  = new string(1000,'\0');
        vector<string *> *cmd_record = new vector<string *>;
        stringstream *ss = new stringstream;

        while(1){

            cout << "calendar # ";

            getline(cin, *cmd);
            delete ss;
            ss = new stringstream;
            *ss << *cmd;

            while(*ss >> *cmd_tmp){
                cmd_record->push_back(cmd_tmp);
                cmd_tmp = new string(1000,'\0');
            }
            if(cmd_record->empty())continue;

            vector<string *>::iterator cmd_it = cmd_record->begin();

            if(**cmd_it == "year"){
                year(cmd_record);
            }else if(**cmd_it == "month"){
                if(month(cmd_record)){
                    print_month(now_month);
                }
            }else if(**cmd_it == "day"){

            }
            
            cmd_it = cmd_record->begin();
            for(;cmd_it!=cmd_record->end();cmd_it++){ 
                delete *cmd_it;
            }
            cmd_record->clear();
        }

       
    }
}


void to_do_list::test(){
    calendar();
}