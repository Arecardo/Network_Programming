/*

*/

#include "character.h"
#include<thread>

int main(){
    // initial
    Buffer b(100);
    producer p(b);
    consumer c(b);

    // initial threads
    std::thread producer_thread(&producer::run, &p);
    std::thread consumer_thread(&consumer::run, &c);

    producer_thread.join();
    consumer_thread.join();
    return 0;
}