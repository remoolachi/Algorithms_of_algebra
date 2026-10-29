#include <iostream>
#include <cassert>

class Exception{
    public:
        virtual const char* er() const{
            return "Error";
        }
        virtual ~Exception() {}
};

class Out_of_range: public Exception{
    public:
        const char* er() const{
            return "index out of range";
        }
};

class Stack_is_empty: public Exception{
    public:
        const char* er() const{
            return "stack is empty";
        }
};
class Vector_is_empty: public Exception{
    public:
        const char* er() const{
            return "vector is empty";
        }
};

class Negative_element: public Exception{
    public:
        const char* er() const{
            return "the number of elements can't be negative";
        }
};

class Eror_in_reading_element: public Exception{
    public:
        const char* er() const{
            return "error in reading elements";
        }
};
class Eror_in_resize: public Exception{
    public:
        const char* er() const{
            return "resize error";
        }
};


class Vector{
    public:
        Vector(){ //конструктор (init)
            size = 0;
            capacity = 10;
            data = new int[capacity];
        }

        ~Vector(){ //деструктор (delete)
            delete[] data;
        }

        //конструктор копирования
        Vector(const Vector& vector2){
            size = vector2.size;
            capacity = vector2.capacity;
            data = new int[capacity];

            for (int i = 0; i < size; i++){
                data[i] = vector2.data[i];
            }
        }

        //оператор присваивания
        Vector& operator =(const Vector& vector2){
            int* temp = new int[vector2.capacity];
            for (int i = 0; i < vector2.size; i++){
                temp[i] = vector2.data[i];
            }
            delete[] data;
            data = temp;
            size = vector2.size;
            capacity = vector2.capacity;

            return *this;
        }

        //оператор []
        int& operator [](int idx){
            if (idx < 0 || idx >= size){
                throw Out_of_range();
            }
            return data[idx];
        }

        int push(int val){
            if (size == capacity){
                if (resize() != 0){
                    throw Eror_in_resize();
                }
            }

            data[size++] = val;
            return 0;
        }

        int pop(){
            if (size == 0){
                throw Vector_is_empty();
            }
            size--;
            return 0;
        }

        void clear(){
            size = 0;
        }

        //оператор ввода
        friend std::istream& operator >>(std::istream& in, Vector& vect){
            int n;
            if (!(in >> n)){
                throw Eror_in_reading_element();
            }
            if (n < 0){
                throw Negative_element();
            }

            vect.clear();
            for (int i = 0; i < n; i++){
                int x;
                if (!(in >> x)){
                    throw Eror_in_reading_element();
                }
                vect.push(x);
            }
            return in;
        }

        //оператор вывода
        friend std::ostream& operator <<(std::ostream& out, Vector& vect){
            for (int i = 0; i < vect.size; i++){
                out << vect.data[i];
                if (i+1 < vect.size) out << " ";
            }
            return out;
        }


    protected:
        int *data = nullptr;
        int size;
        int capacity;

        int resize(){
            int cap;
            if (capacity){
                cap = capacity*2;}

            else cap = 10;


            int *tmp = new int[cap];
            for (int i = 0; i < size; i++) tmp[i] = data[i];
            delete[] data;
            data = tmp;
            capacity = cap;
            return 0;
        }
};



