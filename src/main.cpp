#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <deque>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "../header/user.h"

using namespace std;

void man (int *op);

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
    *ymd = to_string(ltm->tm_year) + *mon_zero + to_string(ltm->tm_mon) + *day_zero + to_string(ltm->tm_mon);
    // vector<int> *ymd = new vector<int>;
    // ymd->push_back(1970 + ltm->tm_year);
    // ymd->push_back(1 + ltm->tm_mon);
    // ymd->push_back(ltm->tm_mday);
    
    to_do_list *tdl = new to_do_list();
    string *cmd = new string(1000,'\0');
    char *edit_mode = new char;
    string *add_name;
    string *add_date;
    string *add_category;
    bool *add_completed;

    add_name = new string(1000,'x');
    add_date = new string(15,'x');
    add_category = new string(1000,'x');
    add_completed = new bool(false);

    *add_name = "none";
    *add_date = "none";
    *add_category = "none";

    string *tmp_name = new string(1000,'\0');
    string *tmp_date = new string(15,'\0');
    string *tmp_category = new string(1000,'\0');
    bool *tmp_completed = new bool(false);

    deque<string *> *cmd_record = new deque<string *>;
    string *cmd_tmp  = new string(1000,'\0');
    stringstream *ss = new stringstream;
    int *op = new int;
    int *error_flag = new int;

    //主介面
	//login(/*fstream*/);
    
    while(1){
        //tdl->debug(); 
        cout << ">";

        //cin.ignore();
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
        auto cmd_it = cmd_record->begin();


        if(**cmd_it == "add"){
            if(cmd_record->empty()){
                *op = 1;
                man(op);
                continue;
            }
            *error_flag = 0;
            cmd_it++;
            while(cmd_it != cmd_record->end()){
                

                if((**cmd_it)[0] == '-' &&  ( (**cmd_it)[1] == 'n' || (**cmd_it)[1] == 'd' || (**cmd_it)[1] == 'c' )){
                    if ((**next(cmd_it))[0] == '-') {
                        cout << "add: option requires an argument -- '" << (**cmd_it)[1] << endl
                             << "Try 'man add' for more information." << endl;
                        break;
                    }
                    if((**cmd_it)[1] == 'n'){
                        *add_name = (**next(cmd_it));
                    }else if((**cmd_it)[1]== 'd'){
                        *add_date = (**next(cmd_it));
                    }else if((**cmd_it)[1] == 'c'){
                        *add_category = (**next(cmd_it));
                    }
                    if(cmd_it != cmd_record->end())cmd_it++;
                    if(cmd_it != cmd_record->end())cmd_it++;
                }else{
                    if((**cmd_it)[0] == '-'){
                        cout << "add: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length())  << "'" << endl 
                            << "Try 'man add' for more information. " << endl;
                    }else{
                        cout << "syntax error: missing flag(s)";
                    }
                    *error_flag = 1;
                    break;
                }

                
            }
            
            if(!(*error_flag)){
                tdl->add(add_name, add_date, add_category, add_completed);
                
                *error_flag = 0;
                
                add_name = new string(1000,'x');
                add_date = new string(15,'x');
                add_category = new string(1000,'x');
                add_completed = new bool(false);

                *add_name = "none";
                *add_date = "none";
                *add_category = "none";
            }
            cmd_it = cmd_record->begin();
            for(;cmd_it!=cmd_record->end();cmd_it++){ 
                delete *cmd_it;
            }
            cmd_record->clear();
        }else if(**cmd_it == "view"){
            if(cmd_record->empty()){
                *op = 2;
                man(op);
                continue;
            }
            *error_flag = 0;
            
            if(cmd_record->size() == 1){
                //預設全輸出
                tdl->view_all_date();
            }else if(cmd_record->size() > 2){
                cout << "view: too many arguments" << endl;
            }else{
                cmd_it++;
                if((**cmd_it)[0] == '-' &&  ( (**cmd_it)[1] == 'w' || (**cmd_it)[1] == 'm' ) ){

                    if((**cmd_it)[1] == 'w'){
                        
                    }else if((**cmd_it)[1]== 'm'){
                        
                    }else if((**cmd_it)[1] == 'c'){
                        
                    }
                    if(cmd_it != cmd_record->end())cmd_it++;
                }else{
                    if((**cmd_it)[0] == '-'){
                        cout << "view: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length()) << endl 
                            << "' Try 'man add' for more information. " << endl;
                    }
                    //*error_flag = 1;
                    break;
                }
            }

            cmd_it = cmd_record->begin();
            for(;cmd_it!=cmd_record->end();cmd_it++){ 
                delete *cmd_it;
            }
            cmd_record->clear();
        }//else if(*s1 == "edit"){
            
        // }else if(*s1 == "del"){

        // }else if(*s1 == "undo"){

        // }else if(*s1 == "redo"){

        // }
        
            // case '1':
                
            // case '2':
            //     //cout << "View Task by Date 0" << endl;
            //     //cout << "View Task by ...?" << endl; //To-Do
            //     tdl->view_all_date();
            //     break;
            // case '3':
            //     tdl->view_all_date();
            //     cout << "Enter a Date to choose a Task: ";
            //     cin >> *tmp_date;
            //     if(!tdl->find_date(tmp_date)){
            //         cout << "No Such Date!!!" << endl;
            //         break;
            //     }
            //     tdl->view_date(tmp_date);
            //     cout << "Enter task Name to Modify: ";
            //     cin >> *tmp_name;
            //     if(!tdl->find_name_date(tmp_name,tmp_date)){
            //         cout << "No Such Name on this Date!!!" << endl;
            //         break;
            //     }
            //     cout << "Modify which Task Attributes: " <<endl;
            //     cout << "Completion(0)" << endl;
            //     cout << "Date(1)" << endl;
            //     cout << "Category(2)" << endl;
            //     cout << "Name(3)" << endl;
            //     cout << ">";
            //     cin >> *edit_mode;
            //     if(*edit_mode == '0'){
            //         cout << "Not completed: (0) Completed: (1) : ";
            //         tdl->edit_completed(tmp_name, tmp_date);
            //     }else if(*edit_mode == '1'){
            //         cout << "Enter new Date: ";
            //         tdl->edit_date(tmp_name, tmp_date);
            //     }else if(*edit_mode == '2'){
            //         cout << "Enter new Category: ";
            //         tdl->edit_category(tmp_name, tmp_date);
            //     }else if(*edit_mode == '3'){
            //         cout << "Enter new Name: ";
            //         tdl->edit_name(tmp_name, tmp_date);
            //     }
            //     break;
            // case '4':
            //     cout << "which task to delete(name): ";
            //     cin >> *tmp_name;
            //     cout << "On which date(year/month/day): ";
            //     cin >> *tmp_date;
            //     tdl->del(tmp_name, tmp_date);
            //     break;
            // case '5':
            //     tdl->undo();
            //     break;
            // case '6':
            //     tdl->redo();       
            //     break;         
            // default:
            //     cout << "please press valid key..." << endl;
            //     *op = '0';
            //     break;
        
    }

    delete now;
    delete ltm;
    delete ymd;
    delete mon_zero;
    delete day_zero;
    delete tdl;
    delete op;
    delete edit_mode;
    delete tmp_name;
    delete tmp_date;
    delete tmp_category;
    delete tmp_completed;
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

void man (int *op){
    if(*op == 0){
        cout << "add task(1)" << endl;
        cout << "view task(2)" << endl;
        cout << "edit task(3)" << endl;
        cout << "delete task(4)" << endl;
        cout << "undo(5) redo(6)" << endl;
    }else if(*op == 1){
        cout << "Usage: add [-n] [-d] [-c]" << endl;
        cout << "-n\tname" << endl;
        cout << "-d\tdate" << endl;
        cout << "-c\tcategory" << endl;
    }
    
}
 

void display_user(){

}

void login(/*fstream*/){
    //文字
	string username;
	cout << "login username: ";
	cin >> username;
	//開檔讀檔
}

