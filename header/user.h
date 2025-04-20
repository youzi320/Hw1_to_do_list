#ifndef USER_H
#define USER_H

#include "to_do_list.h"

extern string *user_name;

using namespace std;

class user{
public:
    user() : u(new set<pair<pair<string*, size_t *>, to_do_list*> *> ){}
    
    pair<pair<string*, size_t *>, to_do_list*> * find_user(string *str);
    pair<pair<string*, size_t *>, to_do_list*> * find_user(string *name, string *password);

    //驗證登入資料
    int login(string *name, string *password);

    //新增user資料至txt檔案中
    int create_user_file(string *name, string *password);
    //新增user資料至set *u中
    int add_user(string *name, string *password);

    int is_user_exist(string *name);
    int is_user_exist(string *name, string *password);

    //刪除txt檔案中的user資料
    int delete_user_file(string *name, string *password);
    //刪除set *u中的user資料
    int del_user(string *name, string *password);

    //執行add, edit, del指令時，更新txt檔案中的資料
    int user_op(string *op, string *username, string *task_name,string *date = 0, string *category = 0, bool *completed = 0, string *type = 0, string *n_str = 0);

    //剛開啟程式時從txt檔讀取資料至set *u中
    int load_user();

    ~user();

private:
    set<pair<pair<string*, size_t *>, to_do_list*> *> *u;
};

extern user *user_;

#endif

