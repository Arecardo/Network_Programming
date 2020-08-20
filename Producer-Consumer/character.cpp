/*

*/

#include "character.h"

// Buffer constructor
Buffer:: Buffer(const int& n)
    :size(n)
{}

void Buffer:: add(int num){
    while(true){
            std::unique_lock<std::mutex> locker(mu); // lock the buff
            cond.wait(locker, [this](){return buffer_.size() < size;}); // condition: only push when buffer is not full
            buffer_.push_back(num);
            std::cout<<"Producer adding: "<<num<<"\n";
            locker.unlock(); // unlock buff
            cond.notify_all(); // notify consumer
            return;
    }
}

void Buffer:: remove(){
    while(true){
        std::unique_lock<std::mutex> locker(mu); // lock the buff
        cond.wait(locker, [this](){return buffer_.size() > 0;}); // remove only when there is something in the buff
        int back = buffer_.back(); // get the number
        buffer_.pop_back(); // remove the number from the deque
        std::cout<<"Consumer removing: "<<back<<"\n";
        locker.unlock(); // unlock buff
        cond.notify_all(); // notify producer
        return;
    }
}

// producer constructor
producer:: producer(Buffer& buffer)
    :buffer_(buffer)
{}

void producer:: run(){
    while(true){
        int num = std::rand() % 100; // get a random number
        buffer_.add(num);
    }
}

// consumer constructor
consumer:: consumer(Buffer& buffer)
    :buffer_(buffer)
{}

void consumer:: run(){
    while(true){
        buffer_.remove();
    }
}