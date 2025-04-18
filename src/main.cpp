#include <iostream> //d ok
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

using namespace std;


int main(){

    time_t *now = new time_t(time(0));
    
    tm *ltm = localtime(&(*now));
    string *ymd = new string(20,'x');
    string *mon_zero = new string(2,'x'), *day_zero = new string(2,'x');
    if(ltm->tm_mon < 10){
        *mon_zero = "/0";
    }else{
        *mon_zero = "/";
    }
    if(ltm->tm_mday < 10){
        *day_zero = "/0";
    }else{
        *day_zero = "/";
    }
    *ymd = to_string(1900+ltm->tm_year) + *mon_zero + to_string(1+ltm->tm_mon) + *day_zero + to_string(ltm->tm_mday);

    to_do_list *tdl = new to_do_list();
    char *edit_mode = new char;

    string *add_name = new string(1000,'x');
    string *add_date = new string(15,'x');
    string *add_category = new string(1000,'x');
    bool *add_completed = new bool(false);

    *add_name = "none";
    *add_date = "none";
    *add_category = "none";

    string *tmp_name = new string(1000,'\0');
    string *tmp_date = new string(15,'\0');
    string *tmp_category = new string(1000,'\0');
    bool *tmp_completed = new bool(false);

    string *cmd = new string(1000,'\0');
    vector<string *> *cmd_record = new vector<string *>;
    string *cmd_tmp  = new string(1000,'\0');
    stringstream *ss = new stringstream;

    string *op = new string(1000,'\0');
    string *register_op = new string(1000,'\0');

    int *tmp_int = new int;
    int *error_flag = new int;


    string *tmp_str = new string(1000,'\0');

    

    char *ch = new char;
    //主介面
	//login(/*fstream*/);
    pair<pair<string*, size_t *>, to_do_list*> *data;
    int *in_login = new int(1); 

    if(user_->load_user() == 0){
        cout << "Error !!!" << endl;
        return 0;
    }
while(1){
    while(*in_login){
        cout << "================================" << endl;
        cout << "      Welcome to To-Do list     " << endl;
        cout << "================================" << endl;
        cout << "Login (1)" << endl;
        cout << "Register(2)" << endl;
        cout << "Delete User(3)" << endl;
        cout << "---------------------" << endl;
        cout << "> " ;
        cin >> *op;
        if(*op == "1"){
            cout << "user name: ";
            cin >> *user_name;
            cout << "password: ";
            cin >> *tmp_str;
            if(user_->login(user_name, tmp_str) == 0){
                cout << endl << endl << "Incorrect User or Incorrect Password!!!" << endl;
                continue;
            }
            *in_login = 0;
        }else if(*op == "2"){
            user_name->clear();
            tmp_str->clear();
            while(1){
                cout << "================================" << endl;
                cout << "          Register Menu         " << endl;
                cout << "================================" << endl;
                cout << "Enter (or Change) User Name: (1)" << endl;
                cout << "Enter (or Change) Password:  (2)" << endl;
                cout << "Comfirm:                     (3)" << endl;
                cout << "Don't Save and Quit:         (4)" << endl;
                cout << "--------------------------------" << endl;
                cout << "Current User Name: ";
                if(user_name->empty()){
                    cout << "none" << endl;;
                }else{
                cout << *user_name << endl;
                }
                cout << "--------------------------------" << endl;
                cout << "> " ;
                cin >> *register_op;

                if(*register_op == "1"){
                    cout << "Enter Name: ";
                    cin >> *user_name;
                }else if(*register_op == "2"){
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
                    cout << endl;
                }else if(*register_op == "3"){
                    if(user_name->empty() || tmp_str->empty()){
                        cout << endl << "User Name or Password is Unset !!!" << endl;
                        continue;
                    }
                    
                    if(user_->create_user_file(user_name, tmp_str) ){
                        user_->add_user(user_name, tmp_str);
                        cout << endl << "User Added Successfully" << endl;
                        break;
                    }else{
                        cout << endl << "User already exists!!!" << endl;
                        continue;
                    }

                    break;
                }else if(*register_op == "4"){
                    user_name->clear();
                    tmp_str->clear();
                    break;
                }else{
                    cout << endl << "Not a valid command..." << endl << endl;
                    continue;
                }
            }
        
            continue;
        }else if(*op == "3"){
            user_name->clear();
            tmp_str->clear();
            while(1){
                cout << "================================" << endl;
                cout << "       User Deletion Menu       " << endl;
                cout << "================================" << endl;
                cout << "Enter (or Change) User Name: (1) " << endl;
                cout << "Comfirm and Delete:          (2) " << endl;
                cout << "Don't Save and Quit:         (3)" << endl;
                cout << "--------------------------------" << endl;
                cout << "Current User Name: ";
                if(user_name->empty()){
                    cout << "none" << endl;;
                }else{
                cout << *user_name << endl;
                }
                cout << "--------------------------------" << endl;
                cout << "> " ;
                cin >> *register_op;

                if(*register_op == "1"){
                    cout << "Enter Name: ";
                    cin >> *user_name;
                }else if(*register_op == "2"){
                    if(user_name->empty()){
                        cout << endl << "User Name is Unset !!!" << endl;
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
                        cout << endl << endl << "User Deleted Successfully" << endl;
                        break;
                    }else{
                        continue;
                    }
                }else if(*register_op == "3"){
                    user_name->clear();
                    tmp_str->clear();
                    break;
                }else{
                    cout << endl << "Not a valid command..." << endl;
                    continue;
                }
            }
        }else{
            cout << endl << "Not a valid command..." << endl;
            continue;
        }
    
    }
        

    data = user_->find_user(user_name);
    tdl = data->second;

    //getline(cin, *cmd);//目前沒有找到清空getline buffer更好的方式
    cin.ignore();

    while(1){
        //tdl->debug(); 
        cout << *ymd << " - " << *user_name <<  " $ ";

        getline(cin, *cmd);
        // ss->clear();
        // ss->str("");
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
            //存檔;
            cmd_it = cmd_record->begin();
            for(;cmd_it!=cmd_record->end();cmd_it++){ 
                delete *cmd_it;
            }
            cmd_record->clear();
            *in_login = 1;
            break;
        }else{
            cout << endl << "No Such Command !!!" << endl;
        }

        cmd_it = cmd_record->begin();
        for(;cmd_it!=cmd_record->end();cmd_it++){ 
            delete *cmd_it;
        }
        cmd_record->clear();
        //存檔;
    }
}

    delete now;
    delete ltm;
    delete ymd;
    delete mon_zero;
    delete day_zero;
    delete ymd;
    delete tdl;
    delete edit_mode;

    delete add_name;
    delete add_date;
    delete add_category;
    delete add_completed;

    delete tmp_name;
    delete tmp_date;
    delete tmp_category;
    delete tmp_completed;

    delete cmd;
    delete cmd_record;
    delete cmd_tmp;
    delete ss;
    delete op;
    delete register_op;
    delete tmp_int;
    delete error_flag;
    delete tmp_str;
    delete ch;
    delete in_login;

    return 0;
}

/*to-do 
登入功能 4.
txt 分別使用者存檔(or json) 5.2
分門別類輸出
視覺化界面
時間排序
簡報上的建議事項 6.
輸出提示字元優化(字型) 7.
改成指標****
增加destructor 2025/04/09
使用virtual(因指標與繼承)
redo-undo 2025/04/09
預設不新增category模式與新增年份模式
刪除new的空間 2025/04/09
改成字串指令(類似linux指令(有flag))(stringstream?) 2.
分多個檔案 1. 2025/04/10
處理使用者資料 3.
新增時間各種模式 5.1
把一些函數改成const
改善輸出(分周)
新增優先順序
增加周箭頭修改模式(ex week up down... row col single)
command 報錯訊息
*/


/* New-To-Do
calendar 新增,刪除,修改指令 (OK)
undone task (OK)
指令簡化(不同指令可用同功能) (No)
讀寫使用者檔案 (OK)

刪除使用者(OK)
註冊使用者功能可退出 (OK)
檢查都用指標
檢查刪除配置空間
檢查作業規定
輸入字串長度檢查
報錯訊息優化(雙空格)
man 功能(readme)
把new strinig(1000, '\0')改掉
檢查

簡化程式碼(如file 的add del ... etc 用一個function並傳入string決定add , del ...etc)
刪除修改新增等結束後輸出調整在函數外，並新增(若原本沒有輸出)
*/
