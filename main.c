#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

struct Node {
    int value;
    int priority;
    struct Node* next;
    struct Node* prev;
};

struct Queue {
    struct Node* first;
    struct Node* last;

};

void push(struct Queue* queue, struct Node* node){

    if(queue->first == NULL && queue->last == NULL){
        node->next = NULL;
        node->prev = NULL;
        queue->first = node;
        queue->last = node;
    }
    else{
        queue->last->prev = node;
        node->next = queue->last;
        node->prev = NULL;
        queue->last = node;
    }

}

void insert(struct Queue* queue, struct Node* node, int priority){
    struct Node* tmp = queue->last;
    while(priority < tmp->priority && tmp->next != NULL){
        tmp = tmp->next;
    }
    //first
    if(tmp->priority > priority) {
        queue->first->next = node;
        node->prev = queue->first;
        node->next = NULL;
        queue->first = node;
    }
    //last
    else if(tmp->prev==NULL){
        tmp->prev = node;
        node->next = tmp;
        node->prev = NULL;
        queue->last = node;
    } // mid, node should be inserted before tmp
    else {
        node->next = tmp;
        node->prev = tmp->prev;
        tmp->prev->next = node;
        tmp->prev = node;
    }


}
void pop(struct Queue* queue) {
    struct Node* tmp = queue->first;
    if(queue->first->prev){
        queue->first->prev->next = NULL;
        queue->first = queue->first->prev;
    }else{
        queue->first = NULL;
    }
    free(tmp);
}

void print(struct Queue* queue){
    if(queue->first){
        struct Node* tmp = queue->first;
        while(1) {
            if(tmp != NULL)  {
                printf("%i value, %i priority\n", tmp->value, tmp->priority);
                tmp = tmp->prev;
            }
            else
                break;
        }
    }else{
        printf("Empty queue");
    }
    printf("\n");
}

void delete_by_priority(struct Queue* queue, int p){
    struct Node* tmp = queue->last;
    while(1){
        if(tmp->priority == p){
            //last
            if(tmp == queue->last) {
                queue->last = tmp->next;
                queue->last->prev = NULL;
                free(tmp);
                tmp = queue->last;
            }
            //first
            else if(tmp == queue->first){
                queue->first = tmp->prev;
                queue->first->next = NULL;
                free(tmp);
                tmp = queue->last;
            }
            //mid
            else{
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                free(tmp);
                tmp = queue->last;
            }
        }
        if(tmp->next != NULL)
            tmp = tmp->next;
        else
            break;
    }
}

void merge_two(struct Queue* queue1, struct Queue* queue2){

    struct Node* tmp = queue2->last;
    while(1){
        struct Node tmp2;
        tmp2.next = tmp->next;
        insert(queue1, tmp, tmp->priority);
        if(tmp2.next!=NULL){
            tmp=tmp2.next;
        }else
            break;
    }
}

int main() {
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->first = NULL;
    queue->last = NULL;

    struct Node* node = malloc(sizeof(struct Node));
    node->value = 1;
    node->priority = 4;
    push(queue, node);
   // print(queue);

    node = malloc(sizeof(struct Node));
    node->value = 2;
    node->priority = 2;
    insert(queue, node, node->priority);
    print(queue);

    node = malloc(sizeof(struct Node));
    node->value = 3;
    node->priority = 1;
    insert(queue, node, node->priority);
    print(queue);

    node = malloc(sizeof(struct Node));
    node->value = 4;
    node->priority = 1;
    insert(queue, node, node->priority);
    print(queue);
    delete_by_priority(queue, 1);
    print(queue);

    struct Queue* sec_queue = (struct Queue*) malloc(sizeof(struct Queue));
    sec_queue->first = NULL;
    sec_queue->last = NULL;

    node = malloc(sizeof(struct Node));
    node->value = 5;
    node->priority = 0;
    push(sec_queue, node);
    print(sec_queue);

    node = malloc(sizeof(struct Node));
    node->value = 13;
    node->priority = 7;
    insert(sec_queue, node, node->priority);
    print(sec_queue);

    merge_two(queue, sec_queue);
    print(queue);


    return 0;
}
