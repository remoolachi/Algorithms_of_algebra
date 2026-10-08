#include <iostream>

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
                throw "index out of range";
            }
            return data[idx];
        }

        int push(int val){
            if (size == capacity) if (resize() != 0) throw "resize error";

            data[size++] = val;
            return 0;
        }

        int pop(){
            if (size == 0){
                throw "vector is empty";
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
                throw "error in reading elements";
            }
            if (n < 0){
                throw "the number of elements can't be negative";
            }

            vect.clear();
            for (int i = 0; i < n; i++){
                int x;
                if (!(in >> x)){
                    throw "error in reading the element";
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
        catch (const char* err){
            std::cout <<err << "\n";
        }

        try{
            Vector empty;
            empty.pop();
        }
        catch (const char* err){
            std::cout << err << "\n";
        }

    }
    catch (const char* err){
        std::cout<< err << "\n";
    }

    return 0;
}
