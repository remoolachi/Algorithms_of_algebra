#include <iostream>
#include <cassert>
#include "vector_with_operators_and_errors.hpp"
//использовать is_sorted и проверить в ассерте


int swap(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}

int partition(int* ar, int l, int r){
    int V = ar[(l+r)/2];
    int i = l;
    int j = r;
    int flag = 0;

    if (i<=j && flag==0){
        while (ar[i]<V){
            i++;
        }
        while (ar[j]>V){
            j--;
        }
        if (i>=j){
            flag = 1;
        }
        swap(ar[i++], ar[j--]);
    }
    return j;
}




void quick_sort(int* ar, int l, int r){
    if (l<r){
        int q = partition(ar, l, r);
        quick_sort(ar, l, q);
        quick_sort(ar, q+1, r);
    }
}

int is_sorted(int* ar, int size){
    int flag = 0;
    for (int i=1; i<size && flag == 0; i++){
        if(ar[i-1]>ar[i]){
            flag = 1;
        }
    }
    return flag;

}

int main(){
    Vector<int> vect;

    vect.push_back(8);
    vect.push_back(1);
    vect.push_back(2);
    vect.push_back(3);

    assert(!is_sorted(vect));

    quick_sort(vect, 0, 3);
    assert(is_sorted(vect));
}


