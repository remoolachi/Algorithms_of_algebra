#ifndef VOE_HPP
#define VOE_HPP
#include <iostream>
#include <cassert>
#include "header.hpp"

class Vector{
    public:
        Vector(){ //конструктор (init)
            sizee = 0;
            capacity = 10;
            data = new int[capacity];
        }

        ~Vector(){ //деструктор (delete)
            delete[] data;
        }

        //конструктор копирования
        Vector(const Vector& vector2){
            sizee = vector2.sizee;
            capacity = vector2.capacity;
            data = new int[capacity];

            for (int i = 0; i < sizee; i++){
                data[i] = vector2.data[i];
            }
        }

        //оператор присваивания
        Vector& operator =(const Vector& vector2){
            int* temp = new int[vector2.capacity];
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
        int& operator [](int idx){
            if (idx < 0 || idx >= sizee){
                throw Out_of_range();
            }
            return data[idx];
        }

        int push(int val){
            if (sizee == capacity){
                if (resize() != 0){
                    throw Eror_in_resize();
                }
            }

            data[sizee++] = val;
            return 0;
        }

        int pop(){
            if (sizee == 0){
                throw Vector_is_empty();
            }
            sizee--;
            return 0;
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
        int *data = nullptr;
        int sizee;
        int capacity;

        int resize(){
            int cap;
            if (capacity){
                cap = capacity*2;}

            else cap = 10;


            int *tmp = new int[cap];
            for (int i = 0; i < sizee; i++) tmp[i] = data[i];
            delete[] data;
            data = tmp;
            capacity = cap;
            return 0;
        }
};

#endif


