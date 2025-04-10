#include "../header/Basic_task.h"
#include "../header/task.h"

task::task(){
    this->name = new string(1000,'\0');//預設需delete?
    this->category = new string(1000,'\0');
    this->completed = new bool(false);

    this->is_new_ = new bool(0);
    this->date = new string(15,'\0');
}

task::task(string *name, string *date, string *category, bool *completed){//預設none?
    this->name = new string(1000,'x');
    this->date = new string(15,'x');
    this->category = new string(15,'x');
    this->completed = new bool(false);
    this->is_new_ = new bool(false);

    *(this->name) = *name;
    *(this->category) = *category;
    *(this->date) = *date;
    *(this->completed) = *completed;
}

task::task(task *copy){//預設none?
    this->name = new string(1000,'x');
    this->date = new string(15,'x');
    this->category = new string(15,'x');
    this->completed = new bool(false);
    this->is_new_ = new bool;

    *(this->name) = *(copy->name);
    *(this->category) = *(copy->category);
    *(this->completed) = *(copy->completed);
    //cout << "this: " << *this->completed << endl;
    *(this->is_new_) = *(copy->is_new_);
    *(this->date) = *(copy->date);
}

void task::view_task(int m_n, int c_n){
    cout << setw(15) << *this->name << setw(15) << *this->date  << setw(15)  << *this->category << setw(15) << *this->completed << endl;  
    cout << "---------------------------------------------------------------" << endl;
}

string * task::get_name() const{
    return this->name;
}

string * task::get_category() const{
    return this->category;
}

string * task::get_date() const{
    return this->date;
} 

bool * task::get_completed() const{
    return this->completed;
}

bool task::is_new() const{ //好像沒用到，之後刪
    return is_new_;
}

task::~task(){
    delete date;
}