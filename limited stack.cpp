#include <iostream>

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




class Stack2 : protected Vector{
    public:
        Stack2() : Vector() {}

        virtual ~Stack2() {}

        Stack2(const Stack2& other) : Vector(other) {}

        Stack2& operator=(const Stack2& other){
            Vector::operator=(other);
            return *this;
        }

        virtual int push(int val){
            return Vector::push(val);
        }

        virtual int pop(){
            if (Vector::size == 0){
                throw Stack_is_empty();
            }
            return Vector::pop();
        }

        virtual int peek(){
            if (Vector::size == 0){
                throw Stack_is_empty();
            }
            return Vector::data[Vector::size - 1];
        }

        bool isEmpty(){
            return Vector::size == 0;
        }

        friend std::ostream& operator <<(std::ostream& out, Stack2& s){
            for (int i = 0; i < s.Vector::size; i++){
                out << s.Vector::data[i];
                if (i+1 < s.Vector::size) out << " ";
            }
            return out;
        }

        friend std::istream& operator >>(std::istream& in, Stack2& s){
            int n;
            if (!(in >> n)){
                throw Eror_in_reading_element();
            }
            if (n < 0){
                throw Negative_element();
            }

            s.Vector::clear();
            for (int i = 0; i < n; i++){
                int x;
                if (!(in >> x)){
                    throw Eror_in_reading_element();
                }
                s.push(x);
            }
            return in;
        }

    private:
        using Vector::operator[];
        using Vector::clear;
        using Vector::resize;
};

class LimitedStack : public Stack2{
    
    private:
        int max_size;

    public:
        LimitedStack(int max) : Stack2(){
            if (max < 0){
                throw Negative_element();
            }
            max_size = max;
        }

        virtual ~LimitedStack() {}

        LimitedStack(const LimitedStack& other) : Stack2(other){
            max_size = other.max_size;
        }

        LimitedStack& operator=(const LimitedStack& other){
            Stack2::operator=(other);
            max_size = other.max_size;
            return *this;
        }

        virtual int push(int val){
            if (Vector::size >= max_size){
                throw Out_of_range();
            }
            return Stack2::push(val);
        }

        virtual int pop(){
            return Stack2::pop();
        }

        virtual int peek(){
            return Stack2::peek();
        }

        int getMaxSize() const{
            return max_size;
        }
};

int main(){
    try{
        Stack2 s;
        s.push(1);
        s.push(2);
        s.push(3);

        std::cout << s << "\n";

        std::cout << s.peek() << "\n";

        s.pop();
        std::cout << s << "\n";

        Stack2 s2 = s;
        std::cout << s2 << "\n";

        Stack2 s3;
        s3.push(100);
        s3 = s;
        std::cout << s3 << "\n";

        Stack2 s4;
        std::cin >> s4;
        std::cout << s4 << "\n";

        try{
            Stack2 empty;
            empty.pop();
        }
        catch (const Stack_is_empty& err){
            std::cout << err.er() << "\n";
        }

        try{
            Stack2 empty;
            empty.peek();
        }
        catch (const Stack_is_empty& err){
            std::cout << err.er() << "\n";
        }
    }
    catch (const Negative_element& err){
        std::cout << err.er() << "\n";
    }
    catch (const Eror_in_reading_element& err){
        std::cout << err.er() << "\n";
    }
    catch (const Exception& err){
        std::cout << err.er() << "\n";
    }

    return 0;
}