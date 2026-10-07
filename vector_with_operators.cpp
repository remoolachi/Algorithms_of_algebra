#include <iostream>

class IntStack{
    private:
        struct Node{
            int value;
            Node* next;
        };
        Node*top;
    
    public:
        IntStack(){
            top = new Node;
            top->value=0;
            top->next = nullptr;
        }
        ~IntStack(){
            while (top!=nullptr){
                Node* nxt = top;
                top = top->next;
                delete nxt;
            }
        }


        //конструктор копирования
        IntStack(const IntStack& other){
            top = new Node;
            top->value = 0;
            top->next = nullptr;

            Node* tail = top;
            Node* curr = other.top->next;

            while (curr != nullptr){
                Node* node = new Node;
                node->value = curr->value;
                node->next = nullptr;
                tail->next = node;
                tail = node;
                curr = curr->next;
            }
        }

        //оператор присваивания
        IntStack& operator=(const IntStack& other){
            while (top != nullptr){
                Node* curr = top;
                top = top->next;
                delete curr;
            }

            top = new Node;
            top->value = 0;
            top->next = nullptr;

            Node* tail = top;
            Node* curr = other.top->next;

            while (curr != nullptr){
                Node* node = new Node;
                node->value = curr->value;
                node->next = nullptr;
                tail->next = node;
                tail = node;
                curr = curr->next;
            }

            return *this;
        }

        //оператор []
        int& operator[](int idx){
            Node* curr = top->next;
            for (int i = 0; i < idx && curr != nullptr; i++){
                curr = curr->next;
            }
            return curr->value;
        }

        void push(int value){
            Node* new_node = new Node;
            new_node->value = value;
            new_node->next = top->next;
            top->next = new_node;
        }

        bool isEmpty(){
            if (top->next==nullptr) return true;
            else return false;
        }

        int pop(){
            if (!isEmpty()){
                Node*temp = top;
                int val = top->value;
                top = top->next;
                delete temp;
                return val;
            }
        }

        int peek(){
            if (isEmpty()) return -1;
            else{
                return top->next->value;
            }
        }

        //оператор ввода
        friend std::istream& operator>>(std::istream& in, IntStack& s){
            int n;
            in >> n;
            
            Node* tail = s.top;
            for (int i = 0; i < n; i++){
                int x;
                in >> x;
                Node* node = new Node;
                node->value = x;
                node->next = nullptr;
                tail->next = node;
                tail = node;
            }

            return in;
        }

        //оператор вывода
        friend std::ostream& operator<<(std::ostream& out, const IntStack& s){
            Node* curr = s.top->next;
            while (curr != nullptr){
                out << curr->value;
                if (curr->next != nullptr) out << " ";
                curr = curr->next;
            }
            return out;
        }


        void print(){
            if (isEmpty()) std::cout<<"Stack is empty";
            else{
                Node* temp = top;
                while (temp->next!=nullptr){
                    std::cout<<temp->value<<"\n";
                    temp=temp->next;
                }
            }
        }
};

int main(){
    IntStack s;
    s.push(1);
    s.push(2);
    s.push(3);

    std::cout << s[0] << "\n";

    s[0] = 100;
    std::cout<< s << "\n";

    s.pop();
    std::cout << s.peek() << "\n";

    IntStack s2 = s;
    std::cout << s2 << "\n";

    IntStack s3;
    s3.push(100);
    s3 = s;
    std::cout << s3 << "\n";

    IntStack s4;
    std::cin >> s4;
    std::cout << s4 << "\n";

    return 0;
}
