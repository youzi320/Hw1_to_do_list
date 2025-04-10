#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>

using namespace std;

class Basic_task {
protected:
 std::string *name;
 std::string *category;
 bool *completed;
};

class task: public Basic_task{
public:  
    task(){
        this->name = new string(1000,'\0');//預設需delete?
        this->category = new string(1000,'\0');
        this->completed = new bool(false);

        this->is_new_ = new bool(0);
        this->date = new string(15,'x');
    }
    task(string *name, string *date, string *category, bool *completed){//預設none?
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
    task(task *copy){//預設none?
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
    void view_task(int m_n, int c_n){
        cout << setw(15) << *this->name << setw(15) << *this->date  << setw(15)  << *this->category << setw(15) << *this->completed << endl;  
        cout << "---------------------------------------------------------------" << endl;
    }
    string * get_name() const{
        return this->name;
    }
    string * get_category() const{
        return this->category;
    }
    string * get_date() const{
        return this->date;
    } 
    bool * get_completed(){
        return this->completed;
    }

    bool is_new() const{
        return is_new_;
    }

    ~task(){
        delete date;
    }
    
private:
    bool *is_new_;
    string *date;
};

class CompareDate
{
    public:
    bool operator() (const task* c1, const task* c2) const{ //原本 &c1 &c2改成 *c1 *c2 可能出錯
        if(*(c1->get_date()) == *(c2->get_date())){
            return *(c1->get_name()) < *(c2->get_name());
        }
        return *(c1->get_date()) < *(c2->get_date());
    }
};

class to_do_list{
public:
    to_do_list() : to_do(new set<task*,CompareDate>),max_name_size(6),max_category_size(10),un_re(new list<pair<int *, pair<task * , task *> > >), idx(0){}
    int find_name_date(string *name, string *date){
        if(to_do == 0){
            return 0;
        }
        set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
        for(;it != (*(this->to_do)).end();it++){
            if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
                return 1;
            }
        }

        return 0;
    }
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
    int find_date(string *date){
        if(to_do == 0){
            return 0;
        }
        set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
        for(;it != (*(this->to_do)).end();it++){
            if(*(*it)->get_date() == *date){
                return 1;
            }
        }

        return 0;
    }
    

    void add(string *name,string *date, string *category, bool *completed, int flag = 1){ //若沒有指定category就是none
        if(this->find_name_date(name, date)){//修改成date一樣, category一樣才重複
            cout << "Task already exists!" << endl;
            return;
        }

        task *tmp = new task(name,date,category, completed);
        //this->new_action
        this->to_do->insert(tmp);
        if(flag == 1)this->new_action(1, tmp, 0); //type list record
        
        max_name_size = max(max_name_size, int((*name).size()));
        max_category_size = max(max_category_size, int((*name).size()));
        // if(*category == "none"){
        //     delete category;
        // }
        return;
    }

    void view_all_date(){
        set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
        string *str;
        str = new string(1000, 'x');
        cout << left;
        cout << setw(15) <<"name:"  << setw(15) << "date:"  << setw(15)  << "category:" << setw(15) << "completed:" << endl;  
        for(;it != (*(this->to_do)).end();it++){               
            (*it)->view_task(max_name_size,max_category_size);
        }
        delete str;
    }

    void view_date(string *date){
        set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
        string *str;
        str = new string(1000, 'x');
        cout << left;
        cout << setw(15) <<"name:"  << setw(15) << "date:"  << setw(15)  << "category:" << setw(15) << "completed:" << endl;  
        for(;it != (*(this->to_do)).end();it++){   
            if(*(*it)->get_date() == *date)(*it)->view_task(max_name_size,max_category_size);
        }
        delete str;
    }

    void edit_name(string *name, string *date){
        set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
        for(;it != (*(this->to_do)).end();it++){
            if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
                task *tmp  = new task(*it);

                string *ptr = (*it)->get_name();
                cin >> *ptr;

                task *new_ = new task(*it);
                this->new_action(3, new_, tmp);
            }
        }
        
    }
    void edit_date(string *name, string *date){
        set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
        for(;it != (*(this->to_do)).end();it++){
            if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
                task *tmp  = new task(*it);

                string *ptr = (*it)->get_date();
                cin >> *ptr;

                task *new_ = new task(*it);
                this->new_action(3, new_, tmp);
            }
        }
    }
    void edit_category(string *name, string *date){
        set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
        for(;it != (*(this->to_do)).end();it++){
            if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
                task *tmp  = new task(*it);

                string *ptr = (*it)->get_category();
                cin >> *ptr;

                task *new_ = new task(*it);
                this->new_action(3, new_, tmp);
            }
        }
    }
    void edit_completed(string *name, string *date){
        set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
        for(;it != (*(this->to_do)).end();it++){
            if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
                task *tmp  = new task(*it);

                bool *ptr = (*it)->get_completed();
                cin >> *ptr;

                task *new_ = new task(*it);
                this->new_action(3, new_, tmp);
            }
        }
    }
//2025/04/09更新每一個日期只能有一個name
//因後來決定只能有特定name只能有一個(之後調整時間不同可以有相同name)
    // void edit(string *name, string *category,string *name_edit,string *category_edit){
    //     set<task*>::iterator it = (*(this->to_do)).begin();
    //     for(;it != (*(this->to_do)).end();it++){
    //         if(*(*it)->get_name() == *name && *(*it)->get_category() == *category){
    //             (*it)->edit(name_edit, category_edit);
    //         }
    //     }
    // }
    void del(string *name, string *date, int flag = 1){
        if(!this->find_name_date(name,date)){
            cout << "No such Task !!!" << endl;
        }
        set<task*, CompareDate>::iterator it = (*(this->to_do)).begin();
        for(;it != (*(this->to_do)).end();it++){
            if(*(*it)->get_name() == *name && *(*it)->get_date() == *date){
                (*(this->to_do)).erase(it);
                return; //不直接return 會出錯
            }
        }
        return;
    }
    void assign_task(task* a, task *t){
        if(a == t)return;
        *(a->get_date()) = *(t->get_date());
        *(a->get_name()) = *(t->get_name());
        *(a->get_category()) = *(t->get_category());
        *(a->get_completed()) = *(t->get_completed());
        return ;
    }
    void new_action(int type, task* ptr_list, task *ptr_record){
        pair<int *, pair<task *,task *> > *ptr = new pair<int *, pair<task *,task *> >;
        ptr->second.first = new task;
        ptr->second.second = new task;

        ptr->first = new int (type);
        if(ptr_list == 0){
            ptr->second.first = 0;
        }else{
            ptr->second.first = new task;
            assign_task(ptr->second.first, ptr_list);
        }
        if(ptr_record == 0){
            ptr->second.second = 0;
        }else{
            ptr->second.second = new task;
            assign_task(ptr->second.second, ptr_record);
        }

        if(un_re->empty()){
            pair<int *, pair<task *,task *> > *zero = new pair<int *, pair<task *, task *> >;
            zero->first = 0;
            zero->second.first = 0;
            zero->second.second = 0;
            un_re->push_back(*zero);
        }else{
            if(idx != prev(un_re->end())){
                un_re->erase(next(idx),un_re->end());
            }
        }
        un_re->push_back(*ptr);
        //this->debug();
        idx = prev(un_re->end());

    }
    void undo(){
        if(this->un_re->empty() || idx == this->un_re->begin()){
            cout << "No Previous Action!" << endl;
            return;
        }
        auto tmp = idx;
        int *op = new int(*(tmp->first));
        task *ptr_list = tmp->second.first; //on the set
        task *ptr_record = tmp->second.second; //record

        if(*op == 1){    
            this->del(ptr_list->get_name(), ptr_list->get_date(), 0);
        }else if(*op == 3){
            this->del(ptr_list->get_name(), ptr_list->get_date(), 0);
            this->add(ptr_record->get_name(), ptr_record->get_date(), ptr_record->get_category(), ptr_record->get_completed(), 0);
        }else if(*op == 4){
            this->add(ptr_record->get_name(), ptr_record->get_date(), ptr_record->get_category(), ptr_record->get_completed(), 0);
        }
        idx--;
        cout << "Undo Operation Done!" << endl;
    }

    void redo(){
        if(this->un_re->empty() || next(idx) == this->un_re->end()){
            cout << "No Later Action!" << endl;
            return;
        }
        auto tmp = next(idx);
        int *op = (tmp->first);
        //cout << "op: " << *op << endl;
        task *ptr_list = tmp->second.first;
        task *ptr_record = tmp->second.second;
        

        if(*op == 1){    
            this->add(ptr_list->get_name(), ptr_list->get_date(), ptr_list->get_category(), ptr_list->get_completed(), 0);
        }else if(*op == 3){
            this->del(ptr_record->get_name(), ptr_record->get_date(), 0);
            this->add(ptr_list->get_name(), ptr_list->get_date(), ptr_list->get_category(), ptr_list->get_completed(), 0);
        }else if(*op == 4){
            this->del(ptr_record->get_name(), ptr_record->get_date(), 0);
        }
        ++idx;
        cout << "Redo Operation Done!" << endl;
        
    }

    ~to_do_list(){
        auto it = this->to_do->begin();
        for(;it != this->to_do->end();it++){
            delete *it;
        }
    }
    void debug(){
        cout << "op: " ;
        list<pair<int *, pair<task* , task *> > >::iterator it = (*un_re).begin();
        it++;
        for(;it!=un_re->end();it++){
            cout << *((*it).first) << " ";
        }cout << endl;
    }
private:
    set<task*, CompareDate> *to_do;
    int max_name_size, max_category_size;
    list<pair<int *, pair<task* , task *> > > *un_re; //pair 之後改pointer指標
    list<pair<int *, pair<task* , task *> > >::iterator idx;
};


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

