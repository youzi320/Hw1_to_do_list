#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "../header/to_do_list.h"

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
    char *op = new char;
    char *edit_mode = new char;
    string *add_name;
    string *add_date;
    string *add_category;
    bool *add_completed;

    string *tmp_name = new string(1000,'x');
    string *tmp_date = new string(15,'x');
    string *tmp_category = new string(1000,'x');
    bool *tmp_completed = new bool(false);
    //主介面
	//login(/*fstream*/);
    
    while(1){
        tdl->debug();
        cout << "add task(1)" << endl;
        cout << "view task(2)" << endl;
        cout << "edit task(3)" << endl;
        cout << "delete task(4)" << endl;
        cout << "undo(5) redo(6)" << endl;
        cout << "> ";
        cin >> *op;
        switch(*op){
            case '1':
                add_name = new string(1000,'x');
                add_date = new string(15,'x');
                add_category = new string(1000,'x');
                add_completed = new bool(false);
                cout << "Enter Task Name(name): ";
                cin >> *add_name;
                cout << "Enter Date(year/month/day): "; //待修改(year簡化)
                cin >> *add_date;
                cout << "Enter Category(category): "; //待修改(year簡化)
                cin >> *add_category;
                tdl->add(add_name, add_date, add_category, add_completed);
                break;
            case '2':
                //cout << "View Task by Date 0" << endl;
                //cout << "View Task by ...?" << endl; //To-Do
                tdl->view_all_date();
                break;
            case '3':
                tdl->view_all_date();
                cout << "Enter a Date to choose a Task: ";
                cin >> *tmp_date;
                if(!tdl->find_date(tmp_date)){
                    cout << "No Such Date!!!" << endl;
                    break;
                }
                tdl->view_date(tmp_date);
                cout << "Enter task Name to Modify: ";
                cin >> *tmp_name;
                if(!tdl->find_name_date(tmp_name,tmp_date)){
                    cout << "No Such Name on this Date!!!" << endl;
                    break;
                }
                cout << "Modify which Task Attributes: " <<endl;
                cout << "Completion(0)" << endl;
                cout << "Date(1)" << endl;
                cout << "Category(2)" << endl;
                cout << "Name(3)" << endl;
                cout << ">";
                cin >> *edit_mode;
                if(*edit_mode == '0'){
                    cout << "Not completed: (0) Completed: (1) : ";
                    tdl->edit_completed(tmp_name, tmp_date);
                }else if(*edit_mode == '1'){
                    cout << "Enter new Date: ";
                    tdl->edit_date(tmp_name, tmp_date);
                }else if(*edit_mode == '2'){
                    cout << "Enter new Category: ";
                    tdl->edit_category(tmp_name, tmp_date);
                }else if(*edit_mode == '3'){
                    cout << "Enter new Name: ";
                    tdl->edit_name(tmp_name, tmp_date);
                }
                break;
            case '4':
                cout << "which task to delete(name): ";
                cin >> *tmp_name;
                cout << "On which date(year/month/day): ";
                cin >> *tmp_date;
                tdl->del(tmp_name, tmp_date);
                break;
            case '5':
                tdl->undo();
                break;
            case '6':
                tdl->redo();       
                break;         
            default:
                cout << "please press valid key..." << endl;
                *op = '0';
                break;
        }
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
txt 分別使用者存檔(or json) 5.
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
改成字串指令(stringstream?) 2.
分多個檔案 1.
處理使用者資料 3.
把一些函數改成const
*/

void menu(){
    
}

void login(/*fstream*/){
    //文字
	string username;
	cout << "login username: ";
	cin >> username;
	//開檔讀檔
}

