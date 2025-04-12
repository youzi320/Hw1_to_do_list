#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "../header/to_do_list.h"

using namespace std;


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
        cout << "-d\tdate" << endl;
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
        cout << "del: too few arguments..." << endl;

    }else if(cmd_record->size() > 2){
        cout << "del: too many arguments..." << endl;
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
