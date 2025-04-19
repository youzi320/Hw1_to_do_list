#ifndef TASK_H
#define TASK_H

#include "Basic_task.h"

using namespace std;

class task: public Basic_task{
public:  
    /*初始化各字串與bool*/
    task();

    /*初始化各字串與bool，分配新空間並copy name,date, category至新空間*/
    task(string *name, string *date, string *category, bool *completed);//預設none?
    
    /*copy constructor 是分配新空間並copy的ptr全複製版本*/
    task(task *copy);

    task(string *date);

    /*輸出task資料*/
    void view_task();

    string * get_name() const;

    string * get_category() const;
    
    string * get_date() const;

    bool * get_completed() const;

    ~task();
    
private:
    string *date;
};


#endif //TASK_H