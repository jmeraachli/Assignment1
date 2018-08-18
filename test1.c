/*
 * src/tutorial/complex.c
 *
 ******************************************************************************
  This file contains routines that can be bound to a Postgres backend and
  called by the backend in the process of processing queries.  The calling
  format for these routines is dictated by Postgres architecture.
******************************************************************************/

#include "postgres.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "fmgr.h"
#include "libpq/pqformat.h"		/* needed for send/recv functions */

PG_MODULE_MAGIC;

typedef struct node* Lnode;
typedef struct list* List;
hhhh
// Create a new list
List newList(void);
// Create a new node
Lnode new_node(int val);
// Append a node to the end of the list
void append(List l, int val);
// Print current list
void printList(List l);
//Destroy list
void destroy(List l);
//Get number of nodes in the list
int num_nodes(List l);
//print list in reverse order
void print_reverse(List l);
// Extracts unique elements of the list
List extract_unique(List l);


struct node{
  int val;
  Lnode next;  
};


struct list{
    Lnode head;
    int num_nodes;
};

Lnode new_node(int val){
    Lnode new = malloc(sizeof(struct node));
    if(new == NULL){
        printf("Out of memory:(\n");
        exit(1);
    }
    new->val = val;
    new->next = NULL;
    return new;
}
List newList(void){
    List new = malloc(sizeof(struct list));
    if(new == NULL){
        printf("Out of memory:(\n");
        exit(1);
    }
    new->head = NULL;
    new->num_nodes = 0;
    return new;
}

void append(List l, int val){
    assert(l != NULL);
    Lnode cur = l->head;
    Lnode new = new_node(val);
    if(cur == NULL){
        l->head = new;
    }else{
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = new;
        
    }
    l->num_nodes++;
}

void printList(List l){
    assert(l!= NULL);
    Lnode cur = l-> head;
    while(cur != NULL){
        printf("[%d]->",cur->val);
        cur = cur->next;
    }
    printf("X\n");
}


void destroy(List l){
    assert(l!= NULL);
    Lnode cur = l->head;
    Lnode prev = NULL;
    // free every single element of the list
    while(cur!= NULL){
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    // free the list structure itself
    free(l);
}
int num_nodes(List l){
    return l->num_nodes;
}

void print_reverse(List l){
    if(l != NULL){
        int i = l->num_nodes;
        while(i > 0){
            Lnode cur = l->head;
            int j = 0;
            while(cur->next != NULL && j < i){
                 cur = cur->next;
                 j++;
            }
            printf("[%d]->",cur->val);
            i--;     
        }
        printf("X\n");    
    }
}

List extract_unique(List l){
    if(l->head != NULL){
        int array[10] = {0};
        Lnode cur = l->head;
        while(cur->next != NULL){
            array[cur->val]++;
            cur = cur->next;
        }
        int i = 0;
        while(i < 10){
            if(array[i] > 0){
                printf("%d->",i);
            }
            i++;    
        }
        printf("X\n");
    }
    return l;
}

typedef struct intSet
{
	List x;
}			intSet;

/*****************************************************************************
 * Input/Output functions
 *****************************************************************************/

PG_FUNCTION_INFO_V1(intSet_in);

Datum
intSet_in(PG_FUNCTION_ARGS)
{
	char	   *str = PG_GETARG_CSTRING(0);
	List x;
	char *getString;
	if (sscanf(str, " (%s)", &getString) != 1)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for complex: \"%s\"",
						str)));
	printf("The length of the getString is: %lu", strlen(getString));





}
