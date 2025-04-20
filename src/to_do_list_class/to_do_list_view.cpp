#include "../../header/user.h"
#include "../../header/sort_cmp.h"
using namespace std;


void to_do_list::view(vector<string *> *cmd_record){

    vector<string *>::iterator cmd_it = cmd_record->begin();

    sort(to_do->begin(), to_do->end(), cmp_completed_date_name);

    if(cmd_record->size() == 1){
        //預設全輸出
        string *type = new string("all");
        view(type);
        delete type;
    }else if(cmd_record->size() > 3){
        cout << endl << "view: too many arguments" << endl << endl;
    }else{
        cmd_it++;
        if(**cmd_it == "-a" || **cmd_it == "-d" || **cmd_it == "-ca" || **cmd_it == "-undone" || **cmd_it == "-done" || **cmd_it == "-n"){

            if( **cmd_it == "-a" ){
                string *type = new string("all");
                view(type);
                delete type;
            }else if( **cmd_it == "-undone" ){
                string *type = new string("undone");
                view(type);
                delete type;
            }else if( **cmd_it == "-done" ){
                string *type = new string("done");
                view(type);
                delete type;
            }else{
                if(cmd_record->size() < 3){
                    cout << endl << "view: too few arguments" << endl << endl;
                    return;
                }else if(cmd_record->size() > 3){
                    cout << endl << "view: too many arguments" << endl << endl;
                    return;
                }else if ((**next(cmd_it))[0] == '-') {
                    cout << endl << "view: option requires an argument -- '" << (**cmd_it)[1] << endl
                                << "Try 'man view' for more information." << endl << endl;
                    return;
                }
                if( **cmd_it == "-d" ){
                    string *type = new string("date");
                    view(type, *next(cmd_it) );
                    delete type;
                }else if( **cmd_it== "-ca" ){
                    string *type = new string("category");
                    view(type, *next(cmd_it) );
                    delete type;
                }else if(**cmd_it== "-n" ){
                    string *type = new string("name");
                    view(type, *next(cmd_it) );
                    delete type;
                }
            }
        }else{
            if((**cmd_it)[0] == '-'){
                cout << endl << "view: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length())  << "'" << endl 
                            << "Try 'man view' for more information. " << endl << endl;
            }
        }
    }
}


void to_do_list::view(string *type, string *str){
    vector<task*>::iterator it = (*(this->to_do)).begin();
    int *flag  = new int(0);

 
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout <<"| name:"  << setw(21) << "| date:"  << setw(25)  << "| category:" << setw(32) << "| completed:         |" << endl; 
    cout << "-------------------------------------------------------------------------------------" << endl;
    for(;it != (*(this->to_do)).end();it++){   
        if(*type == "all"){
            (*it)->view_task();
            *flag = 1;
        }else if(*type == "date" && *(*it)->get_date() == *str){
            (*it)->view_task();
            *flag = 1;
        }else if(*type == "done" && *(*it)->get_completed() == true){
            (*it)->view_task();
            *flag = 1;
        }else if(*type == "undone" && *(*it)->get_completed() == false){
            (*it)->view_task();
            *flag = 1;
        }else if(*type == "category" && *(*it)->get_category() == *str){
            (*it)->view_task();
            *flag = 1;
        }else if(*type == "name" && *(*it)->get_name() == *str){
            (*it)->view_task();
            *flag = 1;
        }
    }

    if(*flag == 0){
        cout << "!!!" << setw(44) << "No Task Yet" << setw(38) << "!!!" << endl << endl;
    }

    delete flag;
}