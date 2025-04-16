#ifndef CMD_REC_h
#define CMD_REC_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <iomanip>
#include "../header/user.h"

using namespace std;

class cmd_rec{
public:
    cmd_rec() : c(new list<string *>){}
    
    void add_cmd(to_do_list *l);

    
private:
    list<string *> *c;
};

#endif

