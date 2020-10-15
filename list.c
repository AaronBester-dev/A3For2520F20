#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


/*Creates a new performance structure*/
struct Performance * newPerformance(){
    struct Performance * perf = malloc(sizeof(struct Performance));
    if(perf == NULL){
        fprintf(stderr,"Error: Couldn't allocate memory for performance structure.\n");
        exit(1);
    }
    perf->reads = 0;
    perf->writes = 0;
    perf->mallocs = 0;
    perf->frees = 0;
    return(perf);
}

/*Adds a new node structure to the beginning of the linked list and changes the head to the newly added node*/
void push(struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width){
    struct Node * newNode = malloc(sizeof(struct Node));
    if(newNode == NULL){
        fprintf(stderr,"Error: Couldn't allocate memory for node structure.\n");
        exit(1);
    }
    newNode->data = malloc(sizeof(char) * width);
    if(newNode->data == NULL){
        fprintf(stderr,"Error: Couldn't allocate memory for data in a node.\n");
        exit(1);
    }

    memcpy(newNode->data,src,width);
    newNode->next = *(list_ptr);
    *(list_ptr) = newNode;
}

/*Reads the data located in the head node of the structure*/
void readHead(struct Performance * performance, struct Node ** list_ptr, void * dest, unsigned int width){
    
    struct Node * temp_ptr = *(list_ptr);
    if(temp_ptr == NULL){
        fprintf(stderr,"Error: Linked list is empty.\n");
        exit(1);
    }

    struct Node * node = *(list_ptr);
    memcpy(dest,node->data, width);
    performance->reads++;

}

/*Removes and frees the head node from the linked list*/
void pop(struct Performance * performance, struct Node ** list_ptr, void * dest, unsigned int width){
    struct Node * temp_ptr = *(list_ptr);
    if(temp_ptr == NULL){
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

/*Returns the next node in the linked list from the node pointed to by the given double pointer*/
struct Node ** next(struct Performance * performance, struct Node ** list_ptr){
    struct Node * temp_ptr = *(list_ptr);
    if(temp_ptr == NULL){
        fprintf(stderr,"Error: Linked list is empty.\n");
        exit(1);
    }

    performance->reads++;
    return(&(temp_ptr->next));
}

/*Returns 1 if linked list is empty and 0 if linked list is not empty*/
int isEmpty(struct Performance * performance, struct Node ** list_ptr){
    struct Node * temp_ptr = *(list_ptr);
     if(temp_ptr == NULL){
        return(1);
    }
    else{
        return(0);
    }
}
/*Frees the entirety of the linked list*/
void freeList(struct Performance * performance, struct Node ** list_ptr){
    while(isEmpty(performance,list_ptr) == 0){
        pop(performance,list_ptr,NULL,0);
    }
}
/*Reads the data located in the node that is wanted by the user*/
void readItem(struct Performance * performance, struct Node ** list_ptr, unsigned int index, void * dest, unsigned int width){
    int i = 0;
    struct Node ** temp_ptr = list_ptr;
    for(i = 0; i < index; i++){
        temp_ptr = (next(performance,temp_ptr));
    }
    readHead(performance,temp_ptr,dest,width);
}
/*Adds a node to the linked list at the end of the list*/
void appendItem(struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width ){
    struct Node ** temp_ptr = list_ptr;

    while(isEmpty(performance,temp_ptr) == 0){
        temp_ptr = (next(performance,temp_ptr));        
    }
    push(performance,temp_ptr,src,width);
}
/*Inserts a new node in the linked list after the node pointed to by the double pointer given to the function*/
void insertItem(struct Performance * performance, struct Node ** list_ptr, unsigned int index, void * src, unsigned int width){
    int i = 0;
    struct Node ** temp_ptr = list_ptr;

    for(i = 0; i < index; i++){
        temp_ptr = (next(performance,temp_ptr));
    }

    push(performance,temp_ptr,src,width);
}
/*Adds a item to the head of the linked list*/
void prependItem(struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width){
    insertItem(performance,list_ptr,0,src,width);
}

/*Deletes and frees a item in the linked list that is pointed to by the double pointer given*/
void deleteItem(struct Performance * performance, struct Node ** list_ptr, unsigned int index){
    int i = 0;
    struct Node ** temp_ptr = list_ptr;

    for(i = 0; i < index; i++){
        temp_ptr = (next(performance,temp_ptr));
    }

    pop(performance,temp_ptr,NULL,0);
}

/*Checks every node in the linked list to see if it contains the same data as given by the user. 
If data is found in the linked list it returns the index of the node it was found in otherwise, it returns -1*/
int findItem(struct Performance * performance, struct Node ** list_ptr, int (*compar)(const void *, const void *), void * target, unsigned int width){
    int i = 0;
    int result = 0;
    struct Node ** temp_ptr = list_ptr;
    void * listItem = malloc(sizeof(char) * width);

    while(isEmpty(performance,temp_ptr) == 0){
        readHead(performance,temp_ptr,listItem,width);
        result = (*compar)(listItem,target);
        if(result == 0){
            free(listItem);
            return(i);
        }
        
        temp_ptr =  (next(performance,temp_ptr));
        i++;
    }

    free(listItem);
    return(-1);
}