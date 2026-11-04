#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "header.hpp"

template <typename T>
class List{
    protected:
        struct Node{
            T value;
            Node* prev;
            Node* next;
            Node(const T& v, Node* p = nullptr, Node* n = nullptr) : value(v), prev(p), next(n) {}
        };

    Node* head;
    Node* tail;
    int sizee;

    public:
        List() : sizee(0){
            head = new Node(T());
            tail = new Node(T());
            head->next = tail;
            tail->prev = head;
        }

        virtual ~List(){
            clear();
            delete head;
            delete tail;
        }

        List(const List& other) : List(){
            Node* cur = other.head->next;
            while (cur != other.tail) {
                push_back(cur->value);
                cur = cur->next;
            }
        }

        List& operator=(const List& other){
            if (this == &other) return *this;
            clear();

            Node* cur = other.head->next;
            while (cur != other.tail){
                push_back(cur->value);
                cur = cur->next;
            }
            return *this;
        }

        void push_back(T val){
            Node* n = new Node(val, tail->prev, tail);
            tail->prev->next = n;
            tail->prev = n;
            sizee++;
        }

        void pop_back(){
            if (sizee == 0) throw Vector_is_empty();
            Node* pop_element = tail->prev;
            pop_element->prev->next = tail;
            tail->prev = pop_element->prev;
            delete pop_element;
            sizee--;
        }

        void push_front(T val){
            Node* n = new Node(val, head, head->next);
            head->next->prev = n;
            head->next = n;
            sizee ++;
        }

        void pop_front(){
            if (sizee == 0) throw Vector_is_empty();
            Node* pop_element = head->next;
            head->next = pop_element->next;
            pop_element->next->prev = head;
            delete pop_element;
            sizee--;
        }

        bool empty(){
            return sizee == 0;
        }

        int  size(){
            return sizee;
        }

        void clear(){
            Node* cur = head->next;
            while (cur != tail){
                Node* nxt = cur->next;
                delete cur;
                cur = nxt;
            }
            head->next = tail;
            tail->prev = head;
            sizee = 0;
        }

        T& operator[](int idx){
            if (idx < 0 || idx >= sizee){
                throw Out_of_range();
            }
            Node* cur = head->next;
            for (int i = 0; i < idx; ++i){
                cur = cur->next;
            }
            return cur->value;
        }

        friend std::istream& operator>>(std::istream& in, List& lst){
            int n;
            if (!(in >> n)){
                throw Eror_in_reading_element();
            }
            if (n < 0){
                throw Negative_element();
            }
            lst.clear();
            for (int i = 0; i < n; ++i){
                T x;
                if (!(in >> x)) throw Eror_in_reading_element();
                lst.push_back(x);
            }
            return in;
        }

        friend std::ostream& operator<<(std::ostream& out, const List& lst){
            bool first = true;
            for (Node* cur = lst.head->next; cur != lst.tail; cur = cur->next){
                if (!first) out << " ";
                out << cur->value;
                first = false;
            }
            return out;
        }

        T& back(){
            if (sizee == 0) throw Vector_is_empty();
            return tail->prev->value;
        }


};
#endif