#include <iostream>
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


void welcome(){
    cout << endl;
    cout << "================================" << endl;
    cout << "      Welcome to To-Do list     " << endl;
    cout << "================================" << endl;
    cout << "Login (1)" << endl;
    cout << "Register(2)" << endl;
    cout << "Delete User(3)" << endl;
    cout << "Quit(4)" << endl;
    cout << "---------------------" << endl;
    cout << "> " ;
}

void register_menu(){
    cout << endl;
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
}

void del_menu(){
    cout << endl;
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
}

void print_user_info(){
    time_t *now = new time_t(time(0));
    
    tm *ltm = localtime(&(*now));
    string *ymd = new string;
    string *mon_zero = new string, *day_zero = new string;

    *mon_zero = ltm->tm_mon < 10 ? "/0" : "/";
    *day_zero = ltm->tm_mday < 10 ? "/0" : "/";

    *ymd = to_string(1900+ltm->tm_year) + *mon_zero + to_string(1+ltm->tm_mon) + *day_zero + to_string(ltm->tm_mday);
    cout << *ymd << " - " << *user_name <<  " $ ";

    delete now;
    delete ymd;
    delete mon_zero;
    delete day_zero;
}
