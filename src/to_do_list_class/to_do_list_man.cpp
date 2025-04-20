#include "../../header/user.h"

using namespace std;

void to_do_list::man (int *op){
    if(*op == 1){
        cout << endl << "Usage: add [-n] [-d] [-ca]" << endl;
        cout << "-n [name]: add new task with name [name]" << endl;
        cout << "-d [date]: add new task with date [date], Format:[year]/[month]/[date], ex. 2025/04/20" << endl;
        cout << "-ca [category]: add new task with category [category]" << endl << endl;
    }else if(*op == 2){
        cout << endl << "Usage: view [-a] [-n] [-d] [-ca] [-done] [-undone]" << endl;
        cout << "-a: view all tasks" << endl;
        cout << "-n [name]: view by name [name]" << endl;
        cout << "-d [date]: view by specific date [date]" << endl;
        cout << "-ca [category]: view by specific category [category]" << endl;
        cout << "-done: view completed tasks" << endl;
        cout << "-undone: view incompleted tasks" << endl << endl;
        
    }else if(*op == 3){
        cout << endl << "Usage: edit [original name] [orginal date] [-n] [-d] [-ca] [-co] " << endl;
        cout << "-n [name]: edit original task's date to [name]" << endl;
        cout << "-d [date]: edit original task's date to [date]" << endl;
        cout << "-ca [category]: edit original task's category to [category]" << endl;
        cout << "-co [1 or 0]: edit original task's completion" << endl << endl;
    }else if(*op == 4){
        cout << endl << "Usage: del [name] [date]" << endl << endl;
    }else if(*op == 5){
        cout << endl << "Calendar mode" << endl << endl;
        cout << "year [year]: set year to [year]" << endl;
        cout << "month [month]: set month to [month]" << endl;
        cout << "day [day]: set  day to [day]" << endl << endl;
        cout << "In calendar mode, you can use [mt] command(After setting the year, month, and day):" << endl;
        cout << "Usage: mt [-e] [-add] [-done] [-del]" << endl;
        cout << "-e [original name] [new name]:  edit task name on specific day" << endl;
        cout << "-add [name]: add new task on specific day" << endl;
        cout << "-done [name]: mark task as completed on specific day by name" << endl;
        cout << "-undone [name]: mark task as incompleted on specific day by name" << endl;
        cout << "-del [name]: delete task on specific day by name" << endl << endl;
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
