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

        int push(int val){
            if (size == capacity){
                if (resize() != 0){
                    return -1;}}

            data[size++] = val;
            return 0;
        }

        int pop(){
            if (size == 0) return -1;
            size--;
            return 0;
        }

        int get(int idx){
            if (idx < 0 || idx >= size) return -1;
            return data[idx];
        }

        void clear(){
            size = 0;
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
    Vector vect;

    int cmd;
    int fl = 1;

    while (fl){
        std::cin >> cmd;

        if (cmd == 1){
            int x;
            std::cin >> x;
            vect.push(x);
        }
        else if (cmd == 2){
            vect.pop();
        }
        else if (cmd == 3){
            int idx;
            std::cin >> idx;
            int x = vect.get(idx);
            std::cout << x << "\n";
        }
        else if (cmd == 4){
            vect.clear();
        }
        else if (cmd == 0){
            std::cout << "bye-bye:)\n";
            fl = 0;
        }
    }

    return 0;
}
