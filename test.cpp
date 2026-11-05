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
            Node* next;
            Node(const T& v, Node* n = nullptr) : value(v), next(n) {}
        };

        Node* head;
        Node* tail;
        int sizee;

        void swap(T& a, T& b){
            T temp = a;
            a = b;
            b = temp;
        }

        Node* partition(Node* l, Node* r){
            Node* t1 = l;
            Node* t2 = l;
            while (t2 != r && t2->next != r){
                t1 = t1->next;
                t2 = t2->next->next;
            }
            T pivot = t1->value;

            Node* i = l;
            Node* j = l;
            bool flag = false;

            while (j != r && !flag){
                if (j->value < pivot){
                    swap(i->value, j->value);
                    i = i->next;
                }
                j = j->next;
                
                if (j == r){
                    flag = true;
                }
            }
            return i;
        }

        void quick_sort(Node* l, Node* r){
            int flag = 0;
            if (l == nullptr || r == nullptr || l == r || l->next == r){
                flag =1;
            }

            if (flag ==0){
                Node* q = partition(l, r);

                if (l != q){
                    quick_sort(l, q);
                }
                
                if (q->next != r){
                    quick_sort(q, r);
                }
            }
        }

    public:
        List() : sizee(0){
            head = nullptr;
            tail = nullptr;
        }

        virtual ~List(){
            clear();
        }

        List(const List& other) : List(){
            Node* cur = other.head;
            while (cur != nullptr) {
                push_back(cur->value);
                cur = cur->next;
            }
        }

        List& operator=(const List& other){
            if (this == &other) return *this;
            clear();
            Node* cur = other.head;
            while (cur != nullptr){
                push_back(cur->value);
                cur = cur->next;
            }
            return *this;
        }

        void push_back(T val){
            Node* n = new Node(val);
            if (tail == nullptr) {
                head = tail = n;
            } else {
                tail->next = n;
                tail = n;
            }
            sizee++;
        }

        void push_front(T val){
            Node* n = new Node(val, head);
            head = n;
            if (tail == nullptr) tail = head;
            sizee++;
        }

        void pop_back(){
            if (sizee == 0) throw Vector_is_empty();
            if (sizee == 1) {
                delete head;
                head = tail = nullptr;
            } else {
                Node* cur = head;
                while (cur->next != tail) {
                    cur = cur->next;
                }
                delete tail;
                tail = cur;
                tail->next = nullptr;
            }
            sizee--;
        }

        void pop_front(){
            if (sizee == 0) throw Vector_is_empty();
            Node* temp = head;
            head = head->next;
            if (head == nullptr) tail = nullptr;
            delete temp;
            sizee--;
        }

        bool empty(){
            return sizee == 0;
        }

        int size(){
            return sizee;
        }

        void clear(){
            Node* cur = head;
            while (cur != nullptr){
                Node* nxt = cur->next;
                delete cur;
                cur = nxt;
            }
            head = nullptr;
            tail = nullptr;
            sizee = 0;
        }

        T& operator[](int idx){
            if (idx < 0 || idx >= sizee){
                throw Out_of_range();
            }
            Node* cur = head;
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
            Node* cur = lst.head;
            while (cur != nullptr){
                if (!first) out << " ";
                out << cur->value;
                first = false;
                cur = cur->next;
            }
            return out;
        }

        T& back(){
            if (sizee == 0) throw Vector_is_empty();
            return tail->value;
        }

        void sort(){
            if (sizee > 1){
                quick_sort(head, nullptr);
            }
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
