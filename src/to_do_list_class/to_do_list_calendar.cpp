#include "../../header/user.h"
#include "../../header/sort_cmp.h"

using namespace std;


void to_do_list::calendar(vector<string *> *cmd_pre){
    if(cmd_pre != 0 && cmd_pre->size() > 1){
        cout << endl << "calendar: too few arguments..." << endl << endl;
    }else{

        int *y = new int(0);
        int *m = new int(0);
        int *w_day = new int(0);

        string *cmd = new string;
        string *cmd_tmp  = new string;
        vector<string *> *cmd_record = new vector<string *>;
        stringstream *ss = new stringstream;
        string *pt_date = new string;

        while(1){

            *pt_date = "\0";

            cout << "calendar ";

            if(*now_year != 0){
                *pt_date = to_string(*now_year);
            }
            if(*now_month != 0){
                if(*now_month < 10){
                    *pt_date += "/0" + to_string(*now_month);
                }else{
                    *pt_date += "/" + to_string(*now_month);
                }
            }
            if(*now_day != 0){
                if(*now_day < 10){
                    *pt_date += "/0" + to_string(*now_day);
            
                }else{
                    *pt_date += "/" + to_string(*now_day);
                }
            }

            if(pt_date->empty()){
                cout << "> ";
            }else{
                cout << *pt_date <<  " > ";
            }
            
            getline(cin, *cmd);
            delete ss;
            ss = new stringstream;
            *ss << *cmd;

            while(*ss >> *cmd_tmp){
                cmd_record->push_back(cmd_tmp);
                cmd_tmp = new string;
            }
            if(cmd_record->empty())continue;

            vector<string *>::iterator cmd_it = cmd_record->begin();

            if(**cmd_it == "year"){
                year(cmd_record);
            }else if(**cmd_it == "month"){
                if(month(cmd_record)){
                    print_month(now_month);
                }
            }else if(**cmd_it == "day"){
                if(day(cmd_record)){
                    print_day(now_month);
                }
            }else if(**cmd_it == "mt"){//manage task
                mt(cmd_record);
            }else if(**cmd_it == "quit"){
                cmd_it = cmd_record->begin();

                for(;cmd_it!=cmd_record->end();cmd_it++){
                    delete *cmd_it;
                }
                delete cmd_record;

                delete y;
                delete m;
                delete w_day;
                delete cmd_tmp;
                delete ss;
                delete pt_date;
                
                return;
            }else{
                cout << endl << "No Such Command !!!" << endl << endl;
            }
            
            cmd_it = cmd_record->begin();
            for(;cmd_it!=cmd_record->end();cmd_it++){ 
                delete *cmd_it;
            }
            cmd_record->clear();
        }

       
    }
}

void to_do_list::mt(vector<string *> *cmd_record){

    if(*now_year == 0 || *now_month == 0 || *now_day == 0){
        cout << endl << "Plase set both Year, Month, and Day before using this command..." << endl << endl;
        return;
    } 

    vector<string *>::iterator cmd_it = cmd_record->begin();

    string *pt_date = new string;

    int *error_flag = new int(0);

    *pt_date = to_string(*now_year);

    *pt_date += *now_month < 10 ? "/0" + to_string(*now_month) : "/" + to_string(*now_month);

    *pt_date += *now_day < 10 ? "/0" + to_string(*now_day) : "/" + to_string(*now_day);

    if(cmd_record->size() == 1){
        cout << endl << "mt: too few arguments" << endl << endl;
        *error_flag = 1;
    }else{
        cmd_it++;
        if(**cmd_it == "-e" || **cmd_it == "-done" || **cmd_it == "-add" || **cmd_it == "-del"){

            if(cmd_record->size() < 3){
                cout << endl << "mt: too few arguments" << endl << endl;
                *error_flag = 1;
            }else if ((**next(cmd_it))[0] == '-') {
                cout << endl << "mt: option requires an argument -- '" << (**cmd_it)[1] << endl << endl;
                *error_flag = 1;
            }else if( **cmd_it == "-e" ){
                if(cmd_record->size() < 4){
                    cout << endl << "mt: too few arguments" << endl << endl;
                    *error_flag = 1;
                }else if(cmd_record->size() > 4){
                    cout << endl << "mt: too many arguments" << endl << endl;
                    *error_flag = 1;
                }else{
                    if(find_name_date((*cmd_record)[2], pt_date)){
                        string *str = new string("name");
                        edit((*cmd_record)[2],  pt_date, (*cmd_record)[3], str);
                        delete str;
                    }else{
                        *error_flag = 1;
                    }  
                }
                
            }else if( **cmd_it == "-done" ){
                if(cmd_record->size() < 3){
                    cout << endl << "mt: too few arguments" << endl << endl;
                    *error_flag = 1;
                }else if(cmd_record->size() > 3){
                    cout << endl << "mt: too many arguments" << endl << endl;
                    *error_flag = 1;
                }else{
                    string *str = new string("name");
                    edit((*cmd_record)[2],  pt_date, 0, str);
                    delete str;
                }
            }else if( **cmd_it == "-add" ){
                if(cmd_record->size() < 3){
                    cout << endl << "mt: too few arguments" << endl << endl;
                    *error_flag = 1;
                }else if(cmd_record->size() > 3){
                    cout << endl << "mt: too many arguments" << endl << endl;
                    *error_flag = 1;
                }else{
                    string *tmp_category = new string("none");
                    bool *tmp_completed = new bool(0);
                    int *flag = new int(1);
                    add((*cmd_record)[2],  pt_date, tmp_category, tmp_completed, flag);
                    delete flag;
                    delete tmp_category;
                    delete tmp_completed;
                }
            }else if( **cmd_it == "-del" ){
                if(cmd_record->size() < 3){
                    cout << endl << "mt: too few arguments" << endl << endl;
                    *error_flag = 1;
                }else if(cmd_record->size() > 3){
                    cout << endl << "mt: too many arguments" << endl << endl;
                    *error_flag = 1;
                }else{
                    int *flag = new int(1);
                    del((*cmd_record)[2],  pt_date, flag);
                    delete flag;
                }
            }
            
        }else{
            if((**cmd_it)[0] == '-'){
                cout << endl << "mt: invalid option -- '" << (*cmd_it)->substr(1,(*cmd_it)->length())  << "'" << endl << endl;
                *error_flag = 1;
            }
        }
    }
    if(!(*error_flag))print_day(now_day);
    
    delete pt_date;
    delete error_flag;
}


void to_do_list::print_month(int *m){

    set<int> *m_31 = new set<int>;

    *m_31 = {1,3,5,7,8,10,12};
    int *d_amt = new int(0);
    int *i = new int;
    int *j = new int;

    if(*m == 2){
        if(check_leap(now_year)){
            *d_amt = 29;
        }else{
            *d_amt = 28;
        }
    }else if(m_31->count(*m)){
        *d_amt = 31;
    }else{
        *d_amt = 30;
    }

   

    struct tm *time = new struct tm;

    memset(time, 0, sizeof(*time));

    time->tm_mday = 1;
    time->tm_mon = *m - 1;
    time->tm_year = *now_year-1900;

    mktime(time);


    cout << "Year: " << *now_year << endl;

    for(*i=0;*i<22*7 + 1;(*i)++){
        cout << "-";
    }cout << endl;
    cout << "|" ;
    cout << setw(12) << "Sun" << setw(10) << "|";
    cout << setw(12) << "Mon" << setw(10) << "|";
    cout << setw(12) << "Tue" << setw(10) << "|";
    cout << setw(12) << "Wed" << setw(10) << "|";
    cout << setw(12) << "Thu" << setw(10) << "|";
    cout << setw(12) << "Fri" << setw(10) << "|";
    cout << setw(12) << "Sat" << setw(10) << "|";
    cout << endl;

    for(*i=0;*i<22*7 + 1;(*i)++){
        cout << "-";
    }cout << endl;

    int *flag = new int(0);
    string *space = new string("                     ");
    int *p_day = new int(1);
    pair< pair< vector<task*>::iterator, vector<task*>::iterator>,  vector<task*>::iterator> **date_task;
    date_task = new pair< pair< vector<task*>::iterator, vector<task*>::iterator>,  vector<task*>::iterator> *[7];

    for(*i=0;*i<7;(*i)++){
        date_task[*i] = new pair< pair< vector<task*>::iterator, vector<task*>::iterator>,  vector<task*>::iterator>;
    }

    

    while(*p_day <= *d_amt){
        cout << "|";
        for(*i=0;*i<7;(*i)++){
            if(*p_day <= *d_amt && (*i == time->tm_wday || *flag == 1)){
                *flag = 1;
                string *pt_month = new string(to_string(*m));
                string *pt_day = new string(to_string(*p_day));
                string *pt_date = new string;

                if(*m < 10){
                    *pt_month = "0" + to_string(*m);
                }
                if(*p_day < 10){
                    *pt_day = "0" + to_string(*p_day);

                }
                (*p_day)++;

                *pt_date = *pt_month + "/" + *pt_day;
                
                cout << setw(13) << *pt_date;
                cout << setw(9) << "|";

                *pt_date = to_string(*now_year) + "/" + *pt_date;

                task *tmp = new task(pt_date);
                
                sort(to_do->begin(), to_do->end(), cmp_date);
                date_task[*i]->first.first = lower_bound(to_do->begin(), to_do->end(), tmp, cmp_date);
                date_task[*i]->first.second = upper_bound(to_do->begin(), to_do->end(), tmp, cmp_date);
                date_task[*i]->second = date_task[*i]->first.first;
                sort(to_do->begin(), to_do->end(), cmp_completed_date_name);

                delete pt_month;
                delete pt_date;
                delete pt_day;
                delete tmp;

            }else{
                cout << *space << "|";
            }
            
        }cout << endl;

        for(*i=0;*i<22*7 + 1;(*i)++){
            cout << "-";
        }cout << endl;

        //for一大格為一天(一大格j小格)
        for(*i=0;*i<6;(*i)++){//每天格數
            cout << "|";
            for(*j=0;*j<7;(*j)++){//七天各跑一遍
                //條件待檢查
                if(date_task[*j]->first.first != date_task[*j]->first.second  &&  date_task[*j]->second != prev(date_task[*j]->first.second) && date_task[*j]->second != date_task[*j]->first.second && *i == 5){
                    cout << setw(21) << "..." << "|";
                }else if((date_task[*j]->first.first != date_task[*j]->first.second) && date_task[*j]->second != date_task[*j]->first.second){
                    cout << setw(18) << *((*date_task[*j]->second)->get_name());
                    if( *((*date_task[*j]->second)->get_completed()) ){
                        cout << "(x)";
                    }else{
                        cout << "( )";
                    }
                    cout << "|";
                    if(date_task[*j]->second != date_task[*j]->first.second)(date_task[*j]->second)++;
                }else{
                    cout << *space << "|";
                }

            }cout << endl;
        }
       for(*i=0;*i < 22*7 + 1;(*i)++){
            cout << "-";
        }cout << endl;

    }

    for(*i=0;*i<7;(*i)++){
        delete date_task[*i];
    }
    delete date_task;
    
    delete m_31;
    delete d_amt;
    delete time;
    delete flag;
    delete space;
    delete p_day;
    delete i;
    delete j;

}

void to_do_list::print_day(int *d){
    string *pt_month = new string(to_string(*now_month));
    string *pt_day = new string(to_string(*now_day));
    string *pt_date = new string;
    int *i = new int;
    int *j = new int;
    
    
    cout << "Year: " << *now_year << endl;

    sort(to_do->begin(), to_do->end(), cmp_date);
    
   
    if(*now_month < 10){
        *pt_month = "0" + to_string(*now_month);
    }
    if(*now_day < 10){
        *pt_day = "0" + to_string(*now_day);

    }
    
    
    *pt_date = *pt_month + "/" + *pt_day;


    for(*i=0;*i<21 + 2;(*i)++){
        cout << "-";
    }cout << endl;

    cout << "|";
    cout << setw(13) << *pt_date << setw(9) << "|" << endl;


    *pt_date = to_string(*now_year) + "/" + *pt_date;

    task *tmp = new task(pt_date);
    vector<task *>::iterator low_it = lower_bound(to_do->begin(), to_do->end(), tmp, cmp_date);
    vector<task *>::iterator up_it = upper_bound(to_do->begin(), to_do->end(), tmp, cmp_date);
    vector<task *>::iterator it = low_it;

    for(*i=0;*i<21 + 2;(*i)++){
        cout << "-";
    }cout << endl;

    if(it == up_it){
        cout << "!!!" << setw(14) << "No Task Yet" << setw(6) << "!!!" << endl << endl;
    }else{
        while(it != up_it){
            cout << "|";

            cout << setw(18) << *((*it)->get_name());

            if(*((*it)->get_completed())){
                cout << "(x)";
            }else{
                cout << "( )";
            }

            cout << "|" << endl;
            
            it++;
        }
        for(*i=0;(*i)<21 + 2;(*i)++){
            cout << "-";
        }cout << endl;
    }    
    

    sort(to_do->begin(), to_do->end(), cmp_completed_date_name);

    delete pt_month;
    delete pt_date;
    delete pt_day;
    delete tmp;
}
