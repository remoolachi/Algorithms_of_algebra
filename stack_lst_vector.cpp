#include <iostream>
#include <cassert>
#include <string>
#include "header.hpp"
#include "list.hpp"
#include "vector_with_operators_and_errors.hpp"

template <typename T, typename Base>
class Stack2 : protected Base{
    public:
        Stack2() : Base() {}
        virtual ~Stack2() {}

        Stack2(const Stack2& other) : Base(other) {}

        Stack2& operator=(const Stack2& other){
            Base::operator=(other);
            return *this;
        }

        int push(T val){
            Base::push_back(val);
            return 0;
        }

        T pop(){
            if (Base::size() == 0){
                throw Stack_is_empty();
            }
            T v = Base::back();
            Base::pop_back();
            return v;
        }

        T peek(){
            if (Base::size() == 0){
                throw Stack_is_empty();
            }
            return Base::back();
        }

        bool isEmpty(){
            return Base::size() == 0;
        }

        friend std::ostream& operator<<(std::ostream& out, Stack2& s){
            int n = s.Base::size();
            for (int i = 0; i < n; ++i){
                out << s.Base::operator[](i);
                if (i+1 < n) out << " ";
            }
            return out;
        }

        friend std::istream& operator>>(std::istream& in, Stack2& s){
            int n;
            if (!(in >> n)){
                throw Eror_in_reading_element();
            }
            if (n < 0){
                throw Negative_element();
            }
            s.Base::clear();
            for (int i = 0; i < n; ++i){
                T x;
                if (!(in >> x)){
                    throw Eror_in_reading_element();
                }
                s.push(x);
            }
            return in;
        }
};


template <typename T, typename Base>
class LimitedStack : public Stack2<T, Base>{
    public:
        LimitedStack(int max) :Stack2<T, Base>(){
            if (max < 0){
                throw Negative_element();
            }
            max_size = max;
        }

        LimitedStack(const LimitedStack& other) : Stack2<T, Base>(other){
            max_size = other.max_size;
        }

        virtual ~LimitedStack() {}

        LimitedStack& operator=(const LimitedStack& other){
            if (this == &other){
                return *this;
            }
            Stack2<T, Base>::operator=(other);
            max_size = other.max_size;
            return *this;
        }

        virtual int push(T val){
            if (this->size() >= max_size){
                throw Stack_is_full();
            }
            return Stack2<T, Base>::push(val);
        }

        bool isFull(){
            return this->size() >= max_size;
        }

        int getMaxSize() const{
            return max_size;
        }
        
    private:
        int max_size;

};


int main(){
    //int (vector)
    {
        Stack2<int, Vector<int>> sv;
        assert(sv.isEmpty());

        sv.push(1);
        sv.push(2);
        sv.push(3);
        assert(!sv.isEmpty());
        assert(sv.peek() == 3);

        assert(sv.pop() == 3);
        assert(sv.peek() == 2);
        assert(sv.pop() == 2);
        assert(sv.pop() == 1);
        assert(sv.isEmpty());

        //копирование
        Stack2<int, Vector<int>> a;
        a.push(10); a.push(20); a.push(30);
        Stack2<int, Vector<int>> b = a;
        assert(b.peek() == 30);
        assert(b.pop() == 30);
        assert(b.pop() == 20);

        //присваивание
        Stack2<int, Vector<int>> c;
        c.push(999);
        c = a;
        assert(c.peek() == 30);
        assert(c.pop() == 30);
        assert(c.pop() == 20);
        assert(c.pop() == 10);
        assert(c.isEmpty());

        //пустой стек
        bool caught = false;
        try { Stack2<int, Vector<int>> e; e.pop(); }
        catch (const Stack_is_empty&){ caught = true; }
        assert(caught);

        caught = false;
        try { Stack2<int, Vector<int>> e; e.peek(); }
        catch (const Stack_is_empty&) { caught = true; }
        assert(caught);
    }

    //int(list)
    {
        Stack2<std::string, List<std::string>> sl;
        assert(sl.isEmpty());

        sl.push("10");
        sl.push("20");
        sl.push("30");
        assert(!sl.isEmpty());
        assert(sl.peek() == "30");

        assert(sl.pop() == "30");
        assert(sl.peek() == "20");
        assert(sl.pop() == "20");
        assert(sl.pop() == "10");
        assert(sl.isEmpty());

        // копирование
        Stack2<std::string, List<std::string>> a;
        a.push("1"); a.push("2"); a.push("3");
        Stack2<std::string, List<std::string>> b = a;
        assert(b.peek() == "3");
        assert(b.pop() == "3");
        assert(b.pop() == "2");

        // присваивание
        Stack2<std::string, List<std::string>> c;
        c.push("999");
        c = a;
        assert(c.peek() == "3");
        assert(c.pop() == "3");
        assert(c.pop() == "2");
        assert(c.pop() == "1");
        assert(c.isEmpty());
    }

    // limited stack double vector
    {
        LimitedStack<double, Vector<double>> lv(3);
        assert(lv.getMaxSize() == 3);
        assert(lv.isEmpty());
        assert(!lv.isFull());

        lv.push(1.0);
        lv.push(2.0);
        lv.push(3.0);
        assert(!lv.isEmpty());
        assert(lv.isFull());
        assert(lv.peek() == 3.0);

        //переполнение
        bool caught = false;
        try { lv.push(4.0); }
        catch (const Stack_is_full&) { caught = true; }
        assert(caught);

        //копирование
        LimitedStack<double, Vector<double>> lv2 = lv;
        assert(lv2.getMaxSize() == 3);
        assert(lv2.peek() == 3.0);

        //присваивание
        LimitedStack<double, Vector<double>> lv3(1);
        lv3.push(777.0);
        lv3 = lv;
        assert(lv3.getMaxSize() == 3);
        assert(lv3.peek() == 3.0);

        //отрицательный лимит
        caught = false;
        try { LimitedStack<double, Vector<double>> bad(-1); }
        catch (const Negative_element&) { caught = true; }
        assert(caught);
    }

    //lim stack float list
    {
        LimitedStack<float, List<float>> ll(2);
        assert(ll.getMaxSize() == 2);
        assert(ll.isEmpty());
        assert(!ll.isFull());

        ll.push(10.0f);
        ll.push(20.0f);
        assert(ll.isFull());
        assert(ll.peek() == 20.0f);

        //переполнение
        bool caught = false;
        try { ll.push(30.0f); }
        catch (const Stack_is_full&) { caught = true; }
        assert(caught);
        assert(ll.peek() == 20.0f);

        //копирование
        LimitedStack<float, List<float>> ll2 = ll;
        assert(ll2.getMaxSize() == 2);
        assert(ll2.peek() == 20.0f);

        //присваивание
        LimitedStack<float, List<float>> ll3(1);
        ll3.push(777.0f);
        ll3 = ll;
        assert(ll3.getMaxSize() == 2);
        assert(ll3.peek() == 20.0f);

        //отрицательный лимит
        caught = false;
        try { LimitedStack<float, List<float>> bad(-1); }
        catch (const Negative_element&) { caught = true; }
        assert(caught);
    }

    std::cout << "All tests passed\n";
    return 0;
}