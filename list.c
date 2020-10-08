#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct Performance * newPerformance(){
    if((struct Performance * perf = malloc(sizeof(struct Performance)) == NULL){
        fprintf(stderr,"Error: Couldn't allocate memory for performance structure.\n");
        exit(1);
    }
    perf->reads = 0;
    perf->writes = 0;
    perf->mallocs = 0;
    perf->frees = 0;
    return(perf);
}

void push(struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width){
    if(struct Node * newNode = malloc(sizeof(struct Node)) == NULL){
        fprintf(stderr,"Error: Couldn't allocate memory for node structure.\n");
        exit(1);
    }

    if((newNode->data = malloc(sizeof(char) * width) == NULL){
        fprintf(stderr,"Error: Couldn't allocate memory for data in a node.\n");
        exit(1);
    }

    memcpy(newNode->data,src,width);
    newNode->next = *(list_ptr);
    *(list_ptr) = newNode;
}

void readHead(struct Performance * performance, struct Node ** list_ptr, void * dest, unsigned int width){
    if(*list_ptr == NULL{
        fprintf(stderr,"Error: Linked list is empty.\n");
        exit(1);
    }

    struct Node * node = *(list_ptr);
    memcpy(dest,node->data, width);
    performance->reads++;

}

void pop(struct Performance * Performance, struct Node ** list_ptr, void * dest, unsigned int width){
    if(*list_ptr == NULL{
        fprintf(stderr,"Error: Linked list is empty.\n");
        exit(1);
    }
    struct Node * nodeToBeFreed = (*(list_ptr));

    memcpy(dest,nodeToBeFreed->data,width);
    *(list_ptr) = nodeToBeFreed->next;
    free(nodeToBeFreed->data);
    free(nodeToBeFreed);
    performance->frees++;
    performance->reads++;
}

struct Node ** next(struct Performance * performance, struct Node ** list_ptr){
    if(*(list_ptr) == NULL{
        fprintf(stderr,"Error: Linked list is empty.\n");
        exit(1);
    }

    performance->reads++;
    return((*(list_ptr)->next));
}

int isEmpty(struct Performance * performance, struct Node ** list_ptr){
     if(*(list_ptr) == NULL{
        return(1);
    }
    else{
        return(0);
    }
}

void freeList(struct Performance * performance, struct Node ** list_ptr){
    while(isEmpty(performance,list_ptr) == 0){
        pop(performance,list_ptr,NULL,0);
    }
}

void readItem(struct Performance * performance, struct Node ** list_ptr, unsigned int index, void * dest, unsigned int width){
    int i = 0;
    struct Node ** temp_ptr = list_ptr;
    for(i = 0; i < index; i++){
        temp_ptr = (next(performance,temp_ptr));
    }
    readHead(performance,temp_ptr,dest,width);
}

void appendItem(struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width ){
    
    
    
    while(isEmpty(performance,list_ptr) == 0){
        
    }
}
