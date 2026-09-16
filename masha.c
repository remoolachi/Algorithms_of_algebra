#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int capacity;
    int size;
} Vector;

void init(Vector *vect){
    vect->capacity = 10;
    vect->data = (int*)malloc(vect->capacity*sizeof(int));
    vect->size = 0;
}


void resize(Vector *vect){
    if (vect->size == vect->capacity){
        vect->capacity *= 2;
        vect->data = (int*)realloc(vect->data, vect->capacity*sizeof(int));
    }
}

int push(Vector *vect, int value){
    resize(vect);

    vect->data[vect->size] = value;
    vect->size++;
    return 0;
}


int pop(Vector *vect){
    if (vect->size == 0) return -1;

    vect->size--;
    vect->data[vect->size] = 0;
    return 0;
}

int get(Vector *vect, int idx){
    if (idx < 0 || idx >= vect->size) return 1e-10;
    return vect->data[idx];
}

  
void clear(Vector *vect){ 
    vect->size = 0;
}

void delete(Vector *vect){
    free(vect->data);

    vect->data = NULL;
    vect->size = 0;
    vect->capacity = 0;
}



int main(void){
    Vector vect;
    init(&vect);

    int cmd;
    int fl = 1;

    while (fl){
        scanf("%d", &cmd);

        if (cmd == 1){
            int x;
            scanf("%d", &x);
            push(&vect, x);
        }

        else if (cmd == 2){
            pop(&vect);
        }

        else if (cmd == 3){
            int idx, x;
            scanf("%d", &idx);
            x = get(&vect, idx);
            printf("%d\n", x);
        }

        else if (cmd == 4){
            clear(&vect);
        }

        else if (cmd == 0){
            delete(&vect);
            printf("bye-bye:)\n");
            fl = 0;
        }
    }

    return 0;
}