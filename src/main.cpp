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

    vector<string *> *cmd_record = new vector<string *>;
    string *cmd_tmp  = new string(1000,'\0');
    stringstream *ss = new stringstream;
    int *op = new int;
    int *tmp_int = new int;
    int *error_flag = new int;


    string *tmp_str= new string(1000,'\0');
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
        }

        cmd_it = cmd_record->begin();
        for(;cmd_it!=cmd_record->end();cmd_it++){ 
            delete *cmd_it;
        }
        cmd_record->clear();
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
    delete tmp_str;
    delete tmp_int;
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


 

void display_user(){

}

void login(/*fstream*/){
    //文字
	string username;
	cout << "login username: ";
	cin >> username;
	//開檔讀檔
}

