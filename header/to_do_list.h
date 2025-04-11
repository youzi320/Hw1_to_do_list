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
#include "CompareDate.h"

using namespace std;


class to_do_list{
public:

    
    to_do_list();
    /*回傳特定task回傳是否在 *to_do set 中*/
    int find_name_date(string *name, string *date) const;
    
    //可能用不到
    // int find_name(string *name){
    //     if(to_do == 0){
    //         return 0;
    //     }
    //     set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
    //     for(;it != (*(this->to_do)).end();it++){
    //         if(*(*it)->get_name() == *name){
    //             return 1;
    //         }
    //     }

    //     return 0;
    // }

    /*回傳特定task回傳是否在*to_do set中*/
    int find_date(string *date) const;
    
    /*新增task到*to_do set中*/
    void add(string *name,string *date, string *category, bool *completed, int flag = 1);
    
    void edit_name(string *name, string *date);

    void edit_date(string *name, string *date);

    void edit_category(string *name, string *date);

    void edit_completed(string *name, string *date);

    void del(string *name, string *date, int flag = 1);

    /*將task* 賦值(new新空間copy)給另一個task * */
    void assign_task(task* a, task *t);
    
    /*紀錄add del edit操作*/
    void new_action(int type, task* ptr_list, task *ptr_record);

    /*根據紀錄的add del edit操作恢復上一步*/
    void undo();

    /*根據紀錄的add del edit操作重做*/
    void redo();

    /*依據date排序輸出所有task*/
    void view_all_date() const;

    /*依據date輸出當日所有task*/
    void view_date(string *date) const;

    ~to_do_list();

    void debug();
private:
    set<task*, CompareDate> *to_do;
    //以下可能不會用到
    int max_name_size, max_category_size;
    list<pair<int *, pair<task* , task *> > > *un_re; //pair 之後改pointer指標
    list<pair<int *, pair<task* , task *> > >::iterator idx;
};

#endif