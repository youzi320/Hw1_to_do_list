#include "../../header/user.h"

using namespace std;

void to_do_list::man (int *op){
    if(*op == 1){
        cout << endl << "Usage: add [-n] [-d] [-ca]" << endl;
        cout << "-n [name]: \tadd new task with name [name]" << endl;
        cout << "-d [date]: \tadd new task with date [date], Format:[year]/[month]/[date], ex. 2025/04/20" << endl;
        cout << "-ca [category]: \tadd new task with category [category]" << endl << endl;
    }else if(*op == 2){
        cout << endl << "Usage: view [-a] [-n] [-d] [-ca] [-done] [-undone]" << endl;
        cout << "-a\tview all tasks" << endl;
        cout << "-a\tview by name" << endl;
        cout << "-d\tview by specific date" << endl;
        cout << "-ca\tview by category" << endl;
        cout << "-done\tview completed tasks" << endl;
        cout << "-undone\tview incompleted tasks" << endl << endl;
        
    }else if(*op == 3){
        cout << endl << "Usage: edit [original name] [orginal date] [-n] [-d] [-ca] [-co] " << endl;
        cout << "-n [name]: \tedit name" << endl;
        cout << "-d [date]: \tedit date" << endl;
        cout << "-ca [category]: \tedit category" << endl;
        cout << "-co [1 or 0]: \tedit completed" << endl << endl;
    }else if(*op == 4){
        cout << endl << "Usage: del [name] [date]" << endl << endl;
    }else if(*op == 5){
        cout << endl << "Usage: calendar" << endl << endl;
        cout << "In calendar mode, you can use [mt] command" << endl << endl;
        cout << "Usage: mt [-e] [-add] [-done] [-del]" << endl;
        cout << "-n [name]: \tedit task name on specific day" << endl;
        cout << "-add [name]: \tadd new task on specific day" << endl;
        cout << "-done [name]: \tmark task as completed on specific day by name" << endl;
        cout << "-del [name]: \tdelete task on specific day by name" << endl << endl;
    }
    
}

void to_do_list::man(vector<string *> *cmd_record){
    int *tmp_int = new int;

    if(cmd_record->size() < 2){
        cout << endl  << "man: too few arguments..." << endl << endl;

    }else if(cmd_record->size() > 2){
        cout << endl << "man: too many arguments..." << endl << endl;
    }else{                  
        if(*(*cmd_record)[1] == "add"){
            *tmp_int = 1;
        }else if(*(*cmd_record)[1] == "view"){
            *tmp_int = 2;
        }else if(*(*cmd_record)[1] == "edit"){
            *tmp_int = 3;
        }else if(*(*cmd_record)[1] == "del"){
            *tmp_int = 4;
        }else if(*(*cmd_record)[1] == "calendar"){
            *tmp_int = 5;
        }
        man(tmp_int);
    }

    delete tmp_int;
}
