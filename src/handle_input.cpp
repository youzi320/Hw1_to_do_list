#include <iostream> //d ok //p ok
#include <string>
#include <vector>
#include <set>
#include <list>
#include <deque>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <conio.h>

#include "../header/user.h"
#include "../header/handle_input.h"
#include "../header/print_line.h"

using namespace std;

int login(){
    string *op = new string("");
    string *register_op = new string;
    string *tmp_str = new string;
    char *ch = new char;
    int *in_login = new int(1);
    
    while(1){
        welcome();
        cin >> *op;
        if(*op == "1"){
            cout << "user name: ";
            cin >> *user_name;
            cout << "password: ";
            cin >> *tmp_str;
            if(user_->login(user_name, tmp_str) != 0){
                break;
            }else{
                cout << endl << endl << "Incorrect User or Incorrect Password!!!" << endl << endl;
            }
        }else if(*op == "2"){
            user_name->clear();
            tmp_str->clear();
            while(1){
                register_menu();

                cin >> *register_op;

                if(*register_op == "1"){
                    cout << "Enter Name: ";
                    cin >> *user_name;
                }else if(*register_op == "2"){
                    tmp_str->clear();
                    cout << "Enter Password: ";
                    while((*ch = getch() ) != '\r'){
                        if(*ch == '\b'){
                            if(!tmp_str->empty()){
                                tmp_str->pop_back();
                                cout << "\b \b";
                            }
                        }else{
                            tmp_str->push_back(*ch);
                            cout << "*";
                        }
                    }
                    cout << endl;
                }else if(*register_op == "3"){
                    if(user_name->empty() || tmp_str->empty()){
                        cout << endl << "User Name or Password is Unset !!!" << endl << endl;
                        continue;
                    }else if(user_->create_user_file(user_name, tmp_str) ){
                        user_->add_user(user_name, tmp_str);
                        cout << endl << "User Added Successfully" << endl << endl;
                        break;
                    }else{
                        cout << endl << "User already exists!!!" << endl << endl;
                        continue;
                    }
                    break;
                }else if(*register_op == "4"){
                    user_name->clear();
                    tmp_str->clear();
                    break;
                }else{
                    cout << endl << "Not a valid command..." << endl << endl;
                }
            }
        }else if(*op == "3"){
            user_name->clear();
            tmp_str->clear();
            while(1){
                del_menu();
                
                if(*register_op == "1"){
                    cout << "Enter Name: ";
                    cin >> *user_name;
                }else if(*register_op == "2"){
                    if(user_name->empty()){
                        cout << endl << "User Name is Unset !!!" << endl << endl;
                        continue;
                    }
                    cout << "Enter Password: ";
                    while((*ch = getch() ) != '\r'){
                        if(*ch == '\b'){
                            if(!tmp_str->empty()){
                                tmp_str->pop_back();
                            }
                            cout << "\b \b";
                        }else{
                            tmp_str->push_back(*ch);
                            cout << "*";
                        }
                    }
                    if(user_->delete_user_file(user_name, tmp_str) == 1){
                        user_->del_user(user_name, tmp_str);
                        cout << endl << endl << "User Deleted Successfully" << endl << endl;
                        break;
                    }
                }else if(*register_op == "3"){
                    user_name->clear();
                    tmp_str->clear();
                    break;
                }else{
                    cout << endl << "Not a valid command..." << endl << endl;
                }
            }
        }else if(*op == "4"){
            cin.ignore();
            delete op;
            delete register_op;
            delete tmp_str;
            delete ch;
            delete in_login;
            return 0;
        }else{
            cout << endl << "Not a valid command..." << endl << endl;
        }
    }

    cin.ignore();
    delete op;
    delete register_op;
    delete tmp_str;
    delete ch;
    delete in_login;

    return 1;
}


void cli(){
    to_do_list *tdl;


    string *cmd = new string;
    vector<string *> *cmd_record = new vector<string *>;
    string *cmd_tmp  = new string;
    stringstream *ss = new stringstream;

    string *tmp_str = new string;

    pair<pair<string*, size_t *>, to_do_list*> *data;

    data = user_->find_user(user_name);
    tdl = data->second;

    while(1){
   
        print_user_info();

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
 
        if(**cmd_it == "add"){
            tdl->add(cmd_record);
            
        }else if(**cmd_it == "view"){
            tdl->view(cmd_record);
        }else if(**cmd_it == "edit"){
           tdl->edit(cmd_record);
        }else if(**cmd_it == "del"){
            tdl->del(cmd_record);
        }else if(**cmd_it == "undo"){
            tdl->undo(cmd_record);
        }else if(**cmd_it == "redo"){
            tdl->redo(cmd_record);
        }else if(**cmd_it == "man"){
           tdl->man(cmd_record);
        }else if(**cmd_it == "calendar" || **cmd_it == "cal"){
            tdl->calendar(cmd_record);
        }else if(**cmd_it == "logout"){
            cmd_it = cmd_record->begin();
            for(;cmd_it!=cmd_record->end();cmd_it++){ 
                delete *cmd_it;
            }
            cmd_record->clear();
            break;
        }else{
            cout << endl << "No Such Command !!!" << endl;
        }

        cmd_it = cmd_record->begin();
        for(;cmd_it!=cmd_record->end();cmd_it++){ 
            delete *cmd_it;
        }
        cmd_record->clear();
    }

    delete ss;
    delete cmd;
    delete cmd_record;
    delete cmd_tmp;
    delete tmp_str;
}
