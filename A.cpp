#include <iostream>
#include <cassert>

class Exception{
    public:
        virtual const char* er() const{
            return "Error";
        }
};

class Out_of_range: public Exception{
    public:
        virtual const char* er() const{
            return "index out of range";
        }
};

class Stack_is_empty: public Exception{
    public:
        virtual const char* er() const{
            return "stack is empty";
        }
};

class Vector_is_empty: public Exception{
    public:
        virtual const char* er() const{
            return "vector is empty";
        }
};

class Negative_element: public Exception{
    public:
        virtual const char* er() const{
            return "the number of elements can't be negative";
        }
};

class Eror_in_reading_element: public Exception{
    public:
        virtual const char* er() const{
            return "error in reading elements";
        }
};

class Eror_in_resize: public Exception{
    public:
        virtual const char* er() const{
            return "resize error";
        }
};

class Stack_is_full : public Exception{
public:
    const char* er() const{
        return "stack is full";
    }
};


template <typename T>
class Vector{
    public:
        Vector(){ //конструктор (init)
            sizee = 0;
            capacity = 10;
            data = new T[capacity];
        }

        ~Vector(){ //деструктор (delete)
            delete[] data;
        }

        //конструктор копирования
        Vector(const Vector& vector2){
            sizee = vector2.sizee;
            capacity = vector2.capacity;
            data = new T[capacity];

            for (int i = 0; i < sizee; i++){
                data[i] = vector2.data[i];
            }
        }

        //оператор присваивания
        Vector& operator =(const Vector& vector2){
            if (this == &vector2){
                return *this;
            }
            T* temp = new T[vector2.capacity];
            for (int i = 0; i < vector2.sizee; i++){
                temp[i] = vector2.data[i];
            }
            delete[] data;
            data = temp;
            sizee = vector2.sizee;
            capacity = vector2.capacity;

            return *this;
        }

        //оператор []
        T& operator [](int idx){
            if (idx < 0 || idx >= sizee){
                throw Out_of_range();
            }
            return data[idx];
        }

        void push_back(T val){
            if (sizee == capacity){
                if (resize() != 0){
                    throw Eror_in_resize();
                }
            }
            data[sizee++] = val;
        }

        void push_front(T val){
            if (sizee == capacity){
                if (resize() != 0){
                    throw Eror_in_resize();
                }
            }
            for (int i = sizee; i > 0; i--){
                data[i] = data[i-1];
            }
            data[0] = val;
            sizee++;
        }

        void pop_back(){
            if (sizee == 0){
                throw Vector_is_empty();
            }
            sizee--;
        }

        void pop_front(){
            if (sizee == 0){
                throw Vector_is_empty();
            }
            for (int i = 0; i < sizee - 1;i++){
                data[i] = data[i + 1];
            }
            sizee--;
        }

        T& back(){
            if (sizee == 0){
                throw Vector_is_empty();
            }
            return data[sizee-1];
        }

        void clear(){
            sizee = 0;
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
                T x;
                if (!(in >> x)){
                    throw Eror_in_reading_element();
                }
                vect.push_back(x);
            }
            return in;
        }

        //оператор вывода
        friend std::ostream& operator <<(std::ostream& out, Vector& vect){
            for (int i = 0; i < vect.sizee; i++){
                out << vect.data[i];
                if (i+1 < vect.sizee) out << " ";
            }
            return out;
        }
        
        int size(){
            return this->sizee;
        }


    protected:
        T *data = nullptr;
        int sizee;
        int capacity;

        int resize(){
            int cap;
            if (capacity){
                cap = capacity*2;}

            else cap = 10;


            T *tmp = new T[cap];
            for (int i = 0; i < sizee; i++) tmp[i] = data[i];
            delete[] data;
            data = tmp;
            capacity = cap;
            return 0;
        }
};


void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

int partition(Vector<int>& ar, int l, int r){
    int V = ar[(l+r)/2];
    int i = l;
    int j = r;
    int flag = false;

    if (i<=j && !flag){
        while (ar[i]<V){
            i++;
        }
        while (ar[j]>V){
            j--;
        }
        if (i>=j){
            flag = true;
        }
        else{
            swap(ar[i], ar[j]);
            i++;
            j--;
        }
    }
    return j;
}


void quick_sort(Vector<int>& ar, int l, int r){
    if (l<r){
        int q = partition(ar, l, r);
        quick_sort(ar, l, q);
        quick_sort(ar, q+1, r);
    }
}

int is_sorted(Vector<int>& ar, int size){
    int flag = true;
    for (int i=1; i<size && flag; i++){
        if(ar[i-1]>ar[i]){
            flag = false;
        }
    }
    return flag;
}

int main(){
    int N;
    std::cin>>N;

    Vector<int> vect;

    for (int i = 0; i<N; i++){
        int x;
        std::cin>>x;
        vect.push_back(x);
    }

    quick_sort(vect, 0, N-1);

    for (int i =0; i<N; i++){
        std::cout << vect[i]<< " ";
    }
    return 0;
}


