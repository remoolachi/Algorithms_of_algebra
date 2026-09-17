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

        void push(int value){
            Node* new_node = new Node;
            new_node->value = value;
            new_node->next = top;
            top = new_node;
        }

        bool isEmpty(){
            if (top->next==nullptr) return true;
            else return false;
        }

        int pop(){
            if (isEmpty()){
                Node*temp = top;
                int val = top->value;
                top = top->next;
                delete temp;
                return val;
            }
            else return -1;
        }

        int peek(){
            if (isEmpty()) return -1;
            else{
                return top->value;
            }
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