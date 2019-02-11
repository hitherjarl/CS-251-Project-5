/*
 
 
 
 by Mohamed Imran Mohamed Siddique
 
 UIN:656951860
 
 E-mail: isiddi5@uic.edu
 
 
 
 */



#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "sq.h"

typedef struct node {
    ElemType val;
    struct node *next;
    struct node *prev;
} NODE;

struct list_struct {
    NODE *front;
    NODE *back;
    int count;
};

struct service_queue {
    LIST * the_queue;
    LIST * buzzers;
    NODE ** queueIndex;
    int size;
};

/* create a new service queue */
// ******Runtime requirement: MET******
SQ * sq_create() {
    SQ *q = malloc(sizeof(SQ));
    
    q->the_queue = lst_create();
    
    q->buzzers = lst_create();
    
    q->queueIndex = malloc(sizeof(NODE*));
    q->size = 0;
    return q;
}

/* deallocate an inputed service queue */
// ******Runtime requirement: MET******
void sq_free(SQ *q) {
    
        lst_free(q->the_queue);
    
            lst_free(q->buzzers);
    
    free(q->queueIndex);
    
        free(q);
    
}

/* display contents of the queue from front to back */
/* 		optional display of the queueIndex array and the buzzer bucket list */
// ******Runtime requirement: MET******
void sq_display(SQ *q) {
    printf("\n");
    printf("The Queue :");
    lst_print(q->the_queue);
}

/* returns length of the queue */
// ******Runtime requirement: MET******
int  sq_length(SQ *q) {
    return lst_length(q->the_queue);
}

/* see sq.h for description */
// ******Runtime requirement: MET******
int  sq_give_buzzer(SQ *q) {
    int buzzer, i;
    
    if(!lst_is_empty(q->buzzers)) {
        
        //setting to top buzzer
        buzzer = lst_pop_front(q->buzzers);
        //push it back
        
        lst_push_back(q->the_queue, buzzer);
        //index is point to the back
        
        q->queueIndex[buzzer] = q->the_queue->back;
        
        return buzzer;

    }
    
    else {
        
        //grow the queueIndex array
        NODE **temp = malloc(sizeof(NODE*) * (lst_length(q->the_queue) + 1));
        
        q->size++;
        //copy to temp
        for(i = 0; i < lst_length(q->the_queue); i++)
            temp[i] = q->queueIndex[i];
        
        //deallocate array
        free(q->queueIndex);
        
        //queueIndex = new allocated
        q->queueIndex = temp;
        
        //set buzzer to the back of queue
        buzzer = sq_length(q);
        
        //push buzzer back of the queue
        lst_push_back(q->the_queue, buzzer);
        
        //queueIndex = buzzer to the back of the queue
        q->queueIndex[buzzer] = q->the_queue->back;
        
        return buzzer;
    }
}

/* see sq.h for description */
// ******Runtime requirement: MET******
int sq_seat(SQ *q) {
    int buzzer;
    
    if(lst_is_empty(q->the_queue)) //if queue is empty reutrn -1
        return -1;
    else{
        
        
        buzzer = lst_pop_front(q->the_queue);
        
        
        lst_push_back(q->buzzers, buzzer);
        
        
        q->queueIndex[buzzer] = NULL;
        
        return buzzer;
    }
}

/* see sq.h for description */
// ******Runtime requirement: MET******
int sq_kick_out(SQ *q, int buzzer) {
    if(q->queueIndex[buzzer] == NULL || sq_length(q) == 0 || buzzer >= q->size)
        
        return 0;
    
    if(q->queueIndex[buzzer] != NULL){ //it is in the queue
        
        //check if kicking the front of the queue
        if(q->the_queue->front->val == buzzer){//if it's at the front
            
            sq_seat(q);
            
            return 1;
        }
        
        
        
        else if(q->the_queue->back->val == buzzer){
            
            q->queueIndex[buzzer] = NULL;
            
            lst_pop_back(q->the_queue); //remove the back
            
            lst_push_back(q->buzzers, buzzer);
            
            
            return 1;
        }
        else{
            
            
            q->queueIndex[buzzer]->prev->next = q->queueIndex[buzzer]->next;
            
                q->queueIndex[buzzer]->next->prev = q->queueIndex[buzzer]->prev;
            
            
            
            free(q->queueIndex[buzzer]);
            
                q->queueIndex[buzzer] = NULL;
            
            
            q->the_queue->count--;
            
           
            
            lst_push_back(q->buzzers, buzzer);
            
            return 1;
        }
    }
    else
        return 0;
}

/* see sq.h for description */
int sq_take_bribe(SQ *q, int buzzer) {
    if(q->queueIndex[buzzer] == NULL || sq_length(q) == 0 || buzzer >= q->size)
        return 0;
    
    
    if(q->the_queue->front->val == buzzer)
            return 1;
    
    
    if(q->the_queue->back->val == buzzer){
        
        
            lst_pop_back(q->the_queue);
        
        
        lst_push_front(q->the_queue, buzzer);
        
        
        q->the_queue->front->next->prev = q->the_queue->front;
        
        return 1;
    }
    else{
        
        lst_push_front(q->the_queue, buzzer);
        
       
            q->the_queue->front->next->prev = q->the_queue->front;
        
        q->queueIndex[buzzer]->prev->next = q->queueIndex[buzzer]->next;
        
            q->queueIndex[buzzer]->next->prev = q->queueIndex[buzzer]->prev;
        
        
        free(q->queueIndex[buzzer]);
        
        q->queueIndex[buzzer] = q->the_queue->front;
        return 1;
    }
}