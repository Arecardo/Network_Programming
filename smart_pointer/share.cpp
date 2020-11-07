/* 
 * A demo for shared_ptr
 * 10/09/2020
*/

// dependencies
#include<iostream>
#include<memory>

template<typename T>
class s_ptr{
private:
    T* _ptr;
    size_t* _count;

public:
    s_ptr(T* ptr = nullptr): _ptr(ptr){ // constructor
        if(_ptr) _count = new size_t(1);
        else _count = new size_t(0);
    }

    s_ptr(const s_ptr& ptr){ // copy constructor
        if(this != &ptr){
            this->_ptr = ptr._ptr;
            this->_count = ptr._count;
            (*this->_count)++;
        }
    }

    s_ptr& operator=(const s_ptr& ptr){ // reload = operator
        // if duplicate
        if(this->_ptr == ptr._ptr) return *this;

        if(this->_ptr){ // if i'm a ptr that is occupied, release the original first
            (*this->_count)--;
            if (this->_count == 0) {
                delete this->_ptr;
                delete this->_count;
            }
        }

        this->_ptr = ptr._ptr;
        this->_count = ptr._count;
        (*this->_count)++;
        return *this;
    }

    T& operator*(){ // reload . operator
        assert(this->_ptr == nullptr);
        return *(this->_ptr);
    }

    T* operator->(){ //  reload -> operator
        assert(this->_ptr == nullptr);
        return this->_ptr;
    }
 
    ~s_ptr(){ // deconstructor
        (*this->_count)--;
        if (*this->_count == 0) {
            delete this->_ptr;
            delete this->_count;
        }
    }
 
    size_t use_count(){
        return *this->_count;
    }
};

int main(){
    {
        s_ptr<int> sp(new int(10)); // initial
        s_ptr<int> sp2(sp); // copy
        s_ptr<int> sp3(new int(20));

        sp2 = sp3;
        std::cout << sp.use_count() << std::endl;
        std::cout << sp3.use_count() << std::endl;
    
    
    } // block end
    return 0;
}