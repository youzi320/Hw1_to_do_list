#ifndef TO_DO_LIST_H
#define TO_DO_LIST_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "task.h"
#include "calendar.h"

using namespace std;


class to_do_list : public calendar{
public:

    
    to_do_list();
    /*回傳特定task回傳是否在 *to_do vecotor中*/
    int find_name_date(string *name, string *date) const;

    /*回傳特定task回傳是否在*to_do vecotor中*/
    int find_date(string *date) const;

    /*新增task到*to_do vecotor中*/
    void add(vector<string *> *cmd_record);
    void add(string *name,string *date, string *category, bool *completed, int *flag);
    
    /*修改*to_do vecotor中的task欄位*/
    void edit(vector<string *> *cmd_record);
    void edit(string *name, string *date, string *str, string *type);

    /*刪除*to_do vecotor中的task*/
    void del(vector<string *> *cmd_record);
    void del(string *name, string *date, int *flag);

    /*將task* 賦值(new新空間copy)給另一個task * */
    void assign_task(task *a, task *t);
    
    /*紀錄add del edit操作*/
    void new_action(int *type, task* ptr_list, task *ptr_record);

    /*根據紀錄的add del edit操作恢復上一步*/
    void undo(vector<string *> *cmd_record);
    int undo();

    /*根據紀錄的add del edit操作重做*/
    void redo(vector<string *> *cmd_record);
    int redo();


    /*輸出指令manual*/
    void man(vector<string *> *cmd_record);
    void man (int *op);

    /*依據指定規則輸出task*/
    void view(vector<string *> *cmd_record);
    void view(string *type, string *str = 0);

    //calendar模式
    void calendar(vector<string *> *cmd_pre = 0);
    //輸出行事曆
    void print_month(int *m);
    //輸出當日task 
    void print_day(int *d);
    //mt(manage task)指令
    void mt(vector<string *> *cmd_record);

    //每次啟動程式時，從txt檔讀取使用者資料
    int load_user();

    ~to_do_list();

private:
    vector<task*> *to_do;

    list<pair<int *, pair<task* , task *> > > *un_re;
    list<pair<int *, pair<task* , task *> > >::iterator idx;
};

#endif