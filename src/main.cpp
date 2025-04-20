#include "../header/user.h"
#include "../header/handle_input.h"

using namespace std;

string *user_name = new string;
user *user_ = new user;

int main(){
    
    
    if(user_->load_user() == 0){
        cout << "Error !!!" << endl;
        return 0;
    }  

    while(1){
        if(!login())break;

        cli();
    }

    delete user_name;
    delete user_;
    return 0;
}

