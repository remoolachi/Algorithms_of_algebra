#include <iostream>

#include "vector_with_operators_and_errors.hpp"






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