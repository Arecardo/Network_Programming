/*

*/

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include<iostream>
#include<deque>
#include<mutex>
#include<condition_variable>

class Buffer{
    public:
        Buffer(const int& n); // construcotr
        ~Buffer(){} // deconstructor
        void add(int num);
        void remove();
    private:
        // mutex and condition_variable
        std:: mutex mu;
        std:: condition_variable cond;

        // initial buffer
        std::deque<int> buffer_;
        unsigned int size = 10;
};

class people{
    public:
        people(){}; // constructor
        ~people(){}; // deconstructor
        virtual void run()=0; // pure virtual run()
};

class producer: public people{
    public:
        producer(Buffer& buffer); //constructor
        ~producer(){}; // deconstructor
        void run();
    private:
        Buffer& buffer_;
};

class consumer: public people{
    public:
        consumer(Buffer& buffer); //constructor
        ~consumer(){}; // deconstructor
        void run();
    private:
        Buffer& buffer_;
};
#endif