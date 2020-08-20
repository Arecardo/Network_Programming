#include<iostream>
#include<thread>
using namespace std;

class bk_task{
public:
    void operator()()const{
        cout<<"fun!"<<endl;
    }
};

int main(){
    
    thread my_thread{(bk_task())};
    my_thread.join();
    
    return 0;
}