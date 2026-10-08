#include <iostream>

class Exception{
    public:
        const char* er() const{
            return "Error";
        }
};

class Out_of_range: public Exception{
    public:
        const char* er() const{
            return "index out of range";
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


    private:
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

int main(){
    try{
        Vector vect;

        vect.push(1);
        vect.push(2);
        vect.push(3);
        vect.pop();
        std::cout<< vect << "\n";

        Vector vect2;
        std::cin >> vect2;
        std::cout << vect2 << "\n";

        Vector vect3;
        vect3 = vect2;
        std::cout << vect3 << "\n";

        try{
            std::cout << vect[100] << "\n";
        }
        catch (const Out_of_range& err){
            std::cout << err.er() << "\n";
        }

        try{
            Vector empty;
            empty.pop();
        }
        catch (const Vector_is_empty& err){
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
