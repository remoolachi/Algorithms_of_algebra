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

    void swap(int& a, int& b){
        int temp = a;
        a = b;
        b = temp;
    }

    Node* partition(Node* l, Node* r){
        Node* t1 = l;
        Node* t2 = l;
        while(t2!=r && t2->next != r){
            t1 = t1->next;
            t2 = t2->next->next;
        }
        int pivot = t1->value;

        Node* i = l;
        Node* j = r;

        int flag = false;

        while (!flag){
            while (i->value < pivot){
                i = i->next;
            }
            while (j->value > pivot){
                j = j->prev;
            }

            if (i==j || i->prev == j){
                flag = true;
            }
            else{
                swap(i->value, j->value);
                i = i->next;
                j = j->prev;
            }
        }
        return j;
    }

    void quick_sort(Node* l, Node* r){
        Node* q = partition(l, r);
        if (l!=q){
            quick_sort(l, q);
        }
        if (q->next!=r && q->next!=nullptr){
            quick_sort(q->next, r);
        }
    }

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

        void sort(){
            quick_sort(head->next, tail->prev);
        }

};

int main(){
    int N;
    std::cin>>N;

    List<int> lst;

    for (int i = 0; i<N; i++){
        int x;
        std::cin>>x;
        lst.push_back(x);
    }

    lst.sort();

    std::cout<<lst;
    return 0;
}
