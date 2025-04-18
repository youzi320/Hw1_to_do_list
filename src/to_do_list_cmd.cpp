#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include "../header/sort_cmp.h"
#include "../header/to_do_list.h"
#include "../header/check.h"



using namespace std;



void to_do_list::add(vector<string *> *cmd_record){
    int *error_flag = new int(0);
    auto cmd_it = cmd_record->begin();

    string *add_name = new string(1000,'x');
    string *add_date = new string(15,'x');
    string *add_category = new string(1000,'x');
    bool *add_completed = new bool(false);

    *add_name = "none";
    *add_date = "none";
    *add_category = "none";

    if(cmd_record->size() == 1){
        cout << "add: too few arguments..." << endl << endl;
        *error_flag = 1;
    }else{
        *error_flag = 0;
        cmd_it++;
        while(cmd_it != cmd_record->end()){ 

            if( (**cmd_it) == "-n" ||  (**cmd_it) == "-d" || (**cmd_it) == "-ca"){
                if (cmd_it == prev(cmd_record->end()) || (**next(cmd_it))[0] == '-') {
                    cout << "add: option requires an argument -- '" << (**cmd_it)[1] << "'" << endl
                        << "Try 'man add' for more information." << endl << endl;
                    *error_flag = 1;
                    break;
                }
                if( (**cmd_it) == "-n"){
                    *add_name = (**next(cmd_it));
                }else if( (**cmd_it) == "-d"){
                    *add_date = (**next(cmd_it));
                    if(!check_date(add_date)){
                        cout <<  "Not a valid date format!!!" << endl;
                        cout << "Should be [year]/[month]/[date], ex. 2025/04/20" << endl << endl;
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
                        << "Try 'man add' for more information. " << endl << endl;
                }else{
                    cout << "syntax error: missing flag(s)" << endl << endl;
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

            cout << endl <<  "Successfully Added !!!" << endl << endl;
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

    sort(to_do->begin(), to_do->end(), cmp_completed_date_name);

    if(cmd_record->size() == 1){
        //預設全輸出
        view_all_date();
    }else if(cmd_record->size() > 3){
        cout << "view: too many arguments" << endl << endl;
    }else{
        cmd_it++;
        if(**cmd_it == "-a" || **cmd_it == "-m" || **cmd_it == "-ca" || **cmd_it == "-undone" || **cmd_it == "-done"){

            if( **cmd_it == "-a" ){
                view_all_date();
            }else if( **cmd_it == "-undone" ){
                view_undone();
            }else if( **cmd_it == "-done" ){
                view_done();
            }else{
                if(cmd_record->size() < 3){
                    cout << "view: too few arguments" << endl << endl;
                }else if(cmd_record->size() > 3){
                    cout << "view: too many arguments" << endl << endl;
                }else if ((**next(cmd_it))[0] == '-') {
                    cout << "view: option requires an argument -- '" << (**cmd_it)[1] << endl
                            << "Try 'man view' for more information." << endl << endl;
                }

                if( **cmd_it == "-d" ){
                    view_date(*next(cmd_it));
                }else if( **cmd_it== "-ca" ){
                    if ((**next(cmd_it))[0] == '-') {
                        cout << "view: option requires an argument -- '" << (**cmd_it)[1] << endl
                            << "Try 'man view' for more information." << endl << endl;
                    }else{
                        //輸出(To-Do)
                    }
                }
            }
        }else{
            if((**cmd_it)[0] == '-'){
                cout << "view: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length())  << "'" << endl 
                    << " Try 'man view' for more information. " << endl << endl;
            }
        }
    }
}

void to_do_list::edit(vector<string *> *cmd_record){

    stringstream *ss;
    int *error_flag = new int(0);
    auto cmd_it = cmd_record->begin();

    string *tmp_name = new string(1000,'x');
    string *tmp_date = new string(15,'x');
    string *tmp_category = new string(1000,'x');
    bool *tmp_completed = new bool(false);

    *tmp_name = "none";
    *tmp_date = "none";
    *tmp_category = "none";

    if(cmd_record->size() < 5){
        cout << "edit: too few arguments..." << endl << endl;
        *error_flag = 1;
    }else if(cmd_record->size() > 5){
        cout << "edit: too many arguments..." << endl << endl;
        *error_flag = 1;
    }else{
        *error_flag = 0;
        cmd_it =  cmd_record->begin()+3;
        if(!find_name_date((*cmd_record)[1], (*cmd_record)[2]) ){
            cout << "No such Task!!!" << endl << endl;
            *error_flag = 1;
        }else if(( (**cmd_it) == "-n" || (**cmd_it) == "-d" || (**cmd_it) == "-ca" || (**cmd_it) == "-co") ){

            if((**cmd_it) == "-n"){
                *tmp_name = (**next(cmd_it));
                edit_name((*cmd_record)[1], (*cmd_record)[2], tmp_name);
            }else if((**cmd_it) == "-d"){
                *tmp_date = (**next(cmd_it));
                if(!check_date(tmp_date)){
                    cout <<  "Not a valid date format!!!" << endl;
                    cout << "Should be [year]/[month]/[date], ex. 2025/04/20" << endl << endl;
                    *error_flag = 1;
                }else{
                    edit_date((*cmd_record)[1], (*cmd_record)[2], tmp_date);
                }
                
            }else if((**cmd_it) == "-ca"){
                *tmp_category = (**next(cmd_it));
                edit_category((*cmd_record)[1], (*cmd_record)[2], tmp_category);
            }else if((**cmd_it) == "-co"){
                if(**next(cmd_it) != "0" && **next(cmd_it) != "1"){
                    cout << "edit: syntax error near unexpected token " << **next(cmd_it) << endl << endl;
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
        view_all_date();
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
        cout << "undo(5) redo(6)" << endl << endl;
    }else if(*op == 1){
        cout << "Usage: add [-n] [-d] [-ca]" << endl;
        cout << "-n\tname" << endl;
        cout << "-d\tdate\tFormat:[year]/[month]/[date], ex. 2025/04/20" << endl;
        cout << "-c\tcategory" << endl << endl;
    }else if(*op == 2){
        cout << "Usage: view [-a] [-m] [-ca]" << endl;
        cout << "-a\tview all task" << endl;
        cout << "-d\tview by specific date" << endl;
        cout << "-c\tview by category" << endl << endl;
    }else if(*op == 3){
        cout << "Usage: edit [original name] [orginal date] [-n] [-d] [-ca] [-co] " << endl;
        cout << "-n\tedit name" << endl;
        cout << "-d\tedit date" << endl;
        cout << "-ca\tedit category" << endl;
        cout << "-co\trdit completed" << endl << endl;
    }else if(*op == 4){
        cout << "Usage: del [name] [date]" << endl << endl;
    }
    
}

void to_do_list::del(vector<string *> *cmd_record){
    int *error_flag = new int(0);

    if(cmd_record->size() < 3){
        cout << "del: too few arguments..." << endl << endl;
        *error_flag = 1;
    }else if(cmd_record->size() > 3){
        cout << "del: too many arguments..." << endl << endl;
        *error_flag = 1;
    }else{                  
        del((*cmd_record)[1], (*cmd_record)[2]);
    }

    if(!(*error_flag)){
        cout << endl << "Successfully Deleted !!!" << endl << endl;
        cout << "Updated To-Do List: " << endl;
        view_all_date();
    }
}

void to_do_list::undo(vector<string *> *cmd_record){
    if(cmd_record->size() > 1){
        cout << "undo: too many arguments..." << endl << endl;
    }else{                  
        if(undo()){
            cout << "Undo Operation Done!" << endl;
        }
    }
}

void to_do_list::redo(vector<string *> *cmd_record){
    if(cmd_record->size() > 1){
        cout << "redo: too many arguments..." << endl << endl;
    }else{                  
        if(redo()){
            cout << "Redo Operation Done!" << endl;
        }
    }
}

void to_do_list::man(vector<string *> *cmd_record){
    int *tmp_int = new int;

    if(cmd_record->size() < 2){
        cout << "man: too few arguments..." << endl << endl;

    }else if(cmd_record->size() > 2){
        cout << "man: too many arguments..." << endl << endl;
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
        cout << "calendar: too few arguments..." << endl << endl;
    }else{

        int *y = new int(0);
        int *m = new int(0);
        int *w_day = new int(0);

        string *cmd = new string(1000,'\0');
        string *cmd_tmp  = new string(1000,'\0');
        vector<string *> *cmd_record = new vector<string *>;
        stringstream *ss = new stringstream;
        string *pt_date = new string("\0");

        while(1){

            *pt_date = "\0";

            cout << "calendar ";

            if(*now_year != 0){
                *pt_date = to_string(*now_year);
            }
            if(*now_month != 0){
                if(*now_month < 10){
                    *pt_date += "/0" + to_string(*now_month);
                }else{
                    *pt_date += "/" + to_string(*now_month);
                }
            }
            if(*now_day != 0){
                if(*now_day < 10){
                    *pt_date += "/0" + to_string(*now_day);
            
                }else{
                    *pt_date += "/" + to_string(*now_day);
                }
            }

            if(pt_date->empty()){
                cout << "> ";
            }else{
                cout << *pt_date <<  " > ";
            }
            
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
                if(day(cmd_record)){
                    print_day(now_month);
                }
            }else if(**cmd_it == "mt"){//manage task
                mt(cmd_record);
            }else if(**cmd_it == "quit"){
                //delete new
                return;
            }else{
                cout << "No Such Command !!!" << endl << endl;
            }
            
            cmd_it = cmd_record->begin();
            for(;cmd_it!=cmd_record->end();cmd_it++){ 
                delete *cmd_it;
            }
            cmd_record->clear();
        }

       
    }
}

void to_do_list::mt(vector<string *> *cmd_record){

    if(*now_year == 0 || *now_month == 0 || *now_day == 0){
        cout << "Plase set both Year, Month, and Day before using this command..." << endl << endl;
        return;
    } 

    auto cmd_it = cmd_record->begin();

    stringstream *ss = new stringstream;
    string *pt_date = new string("\0");

    int *error_flag = new int(0);

    if(*now_year != 0){
        *pt_date = to_string(*now_year);
    }
    if(*now_month != 0){
        if(*now_month < 10){
            *pt_date += "/0" + to_string(*now_month);
        }else{
            *pt_date += "/" + to_string(*now_month);
        }
    }
    if(*now_day != 0){
        if(*now_day < 10){
            *pt_date = "/0" + to_string(*now_day);
    
        }else{
            *pt_date += "/" + to_string(*now_day);
        }
    }

    if(cmd_record->size() == 1){
        cout << "mt: too few arguments" << endl << endl;
        *error_flag = 1;
    }else{
        cmd_it++;
        if(**cmd_it == "-n" || **cmd_it == "-done" || **cmd_it == "-a" || **cmd_it == "-d"){

            if(cmd_record->size() < 3){
                cout << "mt: too few arguments" << endl << endl;
                *error_flag = 1;
            }else if ((**next(cmd_it))[0] == '-') {
                cout << "mt: option requires an argument -- '" << (**cmd_it)[1] << endl << endl;
                *error_flag = 1;
            }else if( **cmd_it == "-n" ){
                if(cmd_record->size() < 4){
                    cout << "mt: too few arguments" << endl << endl;
                    *error_flag = 1;
                }else if(cmd_record->size() > 4){
                    cout << "mt: too many arguments" << endl << endl;
                    *error_flag = 1;
                }else{
                    if(find_name_date((*cmd_record)[2], pt_date)){
                        edit_name((*cmd_record)[2],  pt_date, (*cmd_record)[3]);
                    }else{
                        *error_flag = 1;
                    }  
                }
                
            }else if( **cmd_it == "-done" ){
                if(cmd_record->size() < 3){
                    cout << "mt: too few arguments" << endl << endl;
                    *error_flag = 1;
                }else if(cmd_record->size() > 3){
                    cout << "mt: too many arguments" << endl << endl;
                    *error_flag = 1;
                }else{
                    edit_completed((*cmd_record)[2],  pt_date);
                }
            }else if( **cmd_it == "-a" ){
                if(cmd_record->size() < 3){
                    cout << "mt: too few arguments" << endl << endl;
                    *error_flag = 1;
                }else if(cmd_record->size() > 3){
                    cout << "mt: too many arguments" << endl << endl;
                    *error_flag = 1;
                }else{
                    string *tmp_category = new string("none");
                    bool *tmp_completed = new bool(0);
                    add((*cmd_record)[2],  pt_date, tmp_category, tmp_completed);
                }
            }else if( **cmd_it == "-d" ){
                if(cmd_record->size() < 3){
                    cout << "mt: too few arguments" << endl << endl;
                    *error_flag = 1;
                }else if(cmd_record->size() > 3){
                    cout << "mt: too many arguments" << endl << endl;
                    *error_flag = 1;
                }else{
                    del((*cmd_record)[2],  pt_date);
                }
            }
            
        }else{
            if((**cmd_it)[0] == '-'){
                cout << "mt: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length())  << "'" << endl << endl;
                *error_flag = 1;
            }
        }
    }
    if(!(*error_flag))print_day(now_day);
}

void to_do_list::test(){
    calendar();
}