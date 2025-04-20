#include "../header/Basic_task.h"
#include "../header/task.h"

task::task(){
    this->name = new string;
    this->category = new string;
    this->completed = new bool(false);
    this->date = new string;
}

task::task(string *name, string *date, string *category, bool *completed){//預設none?
    this->name = new string;
    this->date = new string;
    this->category = new string;
    this->completed = new bool(false);

    *(this->name) = *name;
    *(this->category) = *category;
    *(this->date) = *date;
    *(this->completed) = *completed;
}

task::task(task *copy){//預設none?
    this->name = new string;
    this->date = new string;
    this->category = new string;
    this->completed = new bool(false);

    *(this->name) = *(copy->name);
    *(this->category) = *(copy->category);
    *(this->completed) = *(copy->completed);
    *(this->date) = *(copy->date);
}

task::task(string *date){//預設none?
    this->name = new string("none");
    this->date = new string;
    this->category = new string("none");
    this->completed = new bool(false);

    *(this->date) = *date;
}

void task::view_task(){
    cout << "|";
    cout << setw(20) << *this->name << "|" << setw(20) << *this->date << "|" << setw(20)  << *this->category << "|" <<  setw(20) << (*this->completed ? "Yes" : "No") << "|" << endl;  
    cout << "-------------------------------------------------------------------------------------" << endl;
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


task::~task(){
    delete name;
    delete category;
    delete completed;
    delete date;
}