#include "../header/user.h"

using namespace std;

int user::add_user(string *name, string *password){

    if(find_user(name) != 0){
        return 0; 
    }

    to_do_list *l = new to_do_list;
    pair<pair<string*, size_t *>, to_do_list*> *ptr = new pair<pair<string*, size_t *>, to_do_list*>;
    hash<string> *str_hash = new hash<string>;

    ptr->first.first = new string;
    ptr->first.second = new size_t;
    ptr->second = new to_do_list;

    *(ptr->first.first) = *name;
    *(ptr->first.second) = (*str_hash)(*password);

    ptr->second = l;

    (*this->u).insert(ptr);

    delete str_hash;

    return 1;
}

pair<pair<string*, size_t *>, to_do_list*> * user::find_user(string *str){
    set<pair<pair<string*, size_t *>, to_do_list*> *>::iterator it = u->begin();

    for(;it!=(*this->u).end();it++){
        if(*((*it)->first.first) == *str){
            return *it;
        }
    }

    return 0;
}

pair<pair<string*, size_t *>, to_do_list*> * user::find_user(string *name, string *password){
    set<pair<pair<string*, size_t *>, to_do_list*> *>::iterator it = u->begin();
    hash<string> *str_hash = new hash<string>;

    for(;it!=(*this->u).end();it++){
        if(*((*it)->first.first) == *name  && *((*it)->first.second) == (*str_hash)(*password)){
            return *it;
        }
    }

    delete str_hash;

    return 0;
}

int user::del_user(string *name, string *password){
    set<pair<pair<string*, size_t *>, to_do_list*> *>::iterator it = u->begin();
    hash<string> *str_hash = new hash<string>;

    for(;it!=(*this->u).end();it++){
        if(*((*it)->first.first) == *name){
            if(*((*it)->first.second) == (*str_hash)(*password)){
                u->erase(it);
                return 1;
            }else{
                return 0;
            }
        }
    }

    delete str_hash;

    return 0;
}

int user::login(string *name, string *password){
    set<pair<pair<string*, size_t *>, to_do_list*> *>::iterator it = u->begin();
    hash<string> *str_hash = new hash<string>;

    for(;it!=(*this->u).end();it++){
        if(*((*it)->first.first) == *name){
            if(*((*it)->first.second) == (*str_hash)(*password)){
                return 1;
            }else{
                return 0;
            }
        }
    }

    delete str_hash;

    return 0;
}

int user::is_user_exist(string *name){
    fstream *ffile = new fstream("user_file/user_data.txt", ios::in | ios::out | ios::app);
    string *line = new string;

    int *find = new int(0);

    while(getline(*ffile,*line)){
        if(line->find("username: ") == 0){
            if( line->substr(line->find(" ")+1, line->find(" ", line->find(" ")+1)) == *name){
                ffile->close();
                *find = 1;
            }
        }
    }
    ffile->close();

    delete ffile;
    delete line;

    if(*find){
        delete find;
        return 1;
    }else{
        delete find;
        return 0;
    }
}

int user::is_user_exist(string *name, string *password){
    fstream *ffile = new fstream("user_file/user_data.txt", ios::in | ios::out | ios::app);
    string *line = new string;
    hash<string> *str_hash = new hash<string>;
    stringstream *ss;
    size_t *h_s = new size_t;

    int *exist = new int(0);

    while(getline(*ffile,*line) && !(*exist)){
        if(line->find("username: ") == 0){
            if( line->substr(line->find(" ")+1, line->find(" ", line->find(" ")+1)) == *name){
                getline(*ffile,*line);
                ss = new stringstream;
                *ss << *line;
                *ss >> *h_s;
                delete ss;
                if(*h_s == (*str_hash)(*password)){
                    *exist = 1;
                }
            }
        }
    }

    ffile->close();

    delete ffile;
    delete line;
    delete str_hash;
    delete h_s;

    if(*exist){
        delete exist;
        return 1;
    }else{
        delete exist;
        return 0;
    }
}

int user::create_user_file(string *name, string *password){
   
    hash<string> *str_hash = new hash<string>;
    string *line = new string;


    if(is_user_exist(name)){
        return 0;
    }
    

    fstream *ffile = new fstream("user_file/user_data.txt", ios::in | ios::out | ios::app);

    if(!(*ffile)){
        cout << "error" << endl;
        delete ffile;
        delete str_hash;
        delete line;
        return 0;
    }

    *ffile << "username: " << *name << endl;
    *ffile << "password: " << (*str_hash)(*password) << endl;
    *ffile << "---" << endl << endl;

    ffile->close();

    delete ffile;
    delete str_hash;
    delete line;
    return 1;
}

int user::delete_user_file(string *name, string *password){
   
    string *line = new string;
    vector<string> *tmp = new vector<string>;
    int *is_user = new int(0);

    if(!is_user_exist(name)){
        cout << endl  << endl << "Incorrect Username or Password !!!" << endl << endl;
        return 0;
    }

    fstream *ffile = new fstream("user_file/user_data.txt", ios::in);

    if(!(*ffile)){
        cout << "error" << endl;
        delete ffile;
        return 0;
    }

    while(getline(*ffile, *line)){
        if(line->find("username: ") == 0){
            if( line->substr(line->find(" ")+1, line->find(" ", line->find(" ")+1)) == *name){
                *is_user = 1;
            }
        }
        if(!(*is_user)){
            tmp->push_back(*line);
        }else if(*line == "---"){
            getline(*ffile, *line);
            *is_user = 0;
        }
    }

    ffile->close();
    delete ffile;

    ffile = new fstream("user_file/user_data.txt", ios::out);

    vector<string>::iterator it;

    for(it = tmp->begin();it != tmp->end();it++){
        *ffile << *it << endl;
    }

    ffile->close();

    delete line;
    delete tmp;
    delete is_user;
    delete ffile;

    return 1;
}

int user::user_op(string *op, string *username, string *task_name,string *date, string *category, bool *completed, string *type, string *n_str){
    string *line = new string;
    string *task_str = new string;
    vector<string> *tmp = new vector<string>;
    int *is_user = new int(0);

    fstream *ffile = new fstream("user_file/user_data.txt", ios::in);


    if(!(*ffile)){
        cout << "error" << endl;
        delete ffile;
        return 0;
    }
    
    while(getline(*ffile, *line)){
        if(line->find("username: ") == 0){
            if( line->substr(line->find(" ")+1, line->find(" ", line->find(" ")+1)) == *username){
                *is_user = 1;
            }else{
                *is_user = 0;
            }
        }


        if(*op == "add"){
            if(*is_user && *line == "---"){
                *task_str = *task_name + " " + *date + " " + *category + " " + to_string(*completed);
                tmp->push_back(*task_str);
            }
            tmp->push_back(*line);
        }else if(*op == "del"){
            *task_str = *task_name + " " + *date;
            if(*is_user){
                if(line->substr(0,line->find(" ", line->find(" ")+1)) != *task_str){
                    tmp->push_back(*line);
                }
            }else{
                tmp->push_back(*line);
            }
        }else if(*op == "edit"){
            if(*is_user && line->find("username: ") == string::npos && line->find("password: ") == string::npos && *line != ""){
                stringstream *ss = new stringstream;
                *ss << *line;
                string **str = new string *[4];
                int *i = new int;
                for(*i=0;*i < 4;(*i)++){
                    str[*i] = new string;
                    *ss >> *(str[*i]);
                }

                delete ss;

                if(*(str[0]) == *task_name && *(str[1]) == *date){
                    if(*type == "date"){
                        *task_str = *(str[0]) + " " + *n_str + " " + *(str[2]) + " " + *(str[3]);
                    }else if(*type == "name"){
                        *task_str = *n_str + " " + *(str[1]) + " " + *(str[2]) + " " + *(str[3]);
                    }else if(*type == "category"){
                        *task_str = *(str[0]) + " " + *(str[1]) + " " + *n_str + " " + *(str[3]);
                    }else if(*type == "completed"){
                        *task_str = *(str[0]) + " " + *(str[1]) + " " + *(str[2]) + " " + *n_str;
                    }
                    tmp->push_back(*task_str);

                }else{
                    tmp->push_back(*line);
                }

                
                for(*i=0;*i < 4;(*i)++){
                    delete str[*i];
                }
                delete str;
                delete i;
            }else{
                tmp->push_back(*line);
            }
        }
        
    }

    ffile->close();
    delete ffile;

    ffile = new fstream("user_file/user_data.txt", ios::out);

    vector<string>::iterator *it = new vector<string>::iterator;
    int *is_first = new int(1);
    for(*it = tmp->begin();*it != tmp->end();(*it)++){
        *ffile << **it << endl;
    }

    ffile->close();
    
    delete ffile;
    delete line;
    delete task_str;
    delete tmp;
    delete is_user;

    return 1;
}


int user::load_user(){
    string *line = new string;
    stringstream *ss;

    fstream *ffile = new fstream("user_file/user_data.txt", ios::in);
    
    pair<pair<string*, size_t *>, to_do_list*> *user_tmp;

    if(!(*ffile)){
        cout << "error" << endl;
        delete ffile;
        delete line;
        return 0;
    }
    
    while(getline(*ffile, *line)){
        if(line->find("username: ") == 0){
            user_tmp = new pair<pair<string*, size_t *>, to_do_list*>;
            user_tmp->first.first = new string(line->substr(line->find(" ")+1, line->length()));
            user_tmp->first.second = new size_t;
            user_tmp->second = new to_do_list;
            ss = new stringstream;

            getline(*ffile, *line);
            
            *ss << line->substr(line->find(" ")+1, line->length());

            *ss >> *user_tmp->first.second;

            delete ss;

            while(getline(*ffile, *line)){
                if(*line == "---"){
                    user_->u->insert(user_tmp);
                    break;
                }

                ss = new stringstream;
                *ss << *line;
                string **str = new string *[4];
                int *i = new int;
                for(*i=0;*i < 4;(*i)++){
                    str[*i] = new string;
                    *ss >> *(str[*i]);
                }
                bool *b_tmp = new bool;
                if(*(str[3]) == "0"){
                    *b_tmp = false;
                }else if(*(str[3]) == "1"){
                    *b_tmp = true;
                }
                int *flag = new int(0);
                user_tmp->second->add((str[0]), (str[1]), (str[2]), b_tmp, flag);
                delete flag;

                delete ss;
                for(*i=0;*i < 4;(*i)++){
                    delete str[*i];
                }
                delete str;
                delete i;
                delete b_tmp;
            }
        }
        
    }
    
    ffile->close();
    delete ffile;
    delete line;

    return 1;
}   

user::~user(){
    set<pair<pair<string*, size_t *>, to_do_list*> *>::iterator it = u->begin();
    for(;it!=u->end();it++){
        delete (*it)->first.first;
        delete (*it)->first.second;
        delete (*it)->second;
    }
    delete u;
}