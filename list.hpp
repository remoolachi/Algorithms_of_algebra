#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "header.hpp"

template <typename T>
class List{
    protected:
        struct Node{
        T value;
        Node* next;
        Node(T v, Node* n = nullptr) : value(v), next(n) {}
    };

    Node* head;
    int size;



}