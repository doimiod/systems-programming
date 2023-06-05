#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
  struct listset * result;
  result = malloc(sizeof(struct listset)); 
  assert (result != NULL); //assert.h
  result-> head = NULL;
  return result;

}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {

  struct listnode * p;
  p = malloc(sizeof(struct listnode));
  for ( p = this->head; p != NULL; p = p->next )
  {
    if(strcmp(p->str,item)==0)
    {
      return 1;
      break;
    }
  }
  return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item) {

  if(listset_lookup(this, item) == 0)
  {
    struct listnode * node;
    node = malloc(sizeof(struct listnode));
    node->str = item;
    node->next = this->head; //item should go head so thats why.
    this->head = node;
  }
  
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
  
    //boolean deleted = false;
    int n=0;
    struct listnode * node;
    node = malloc(sizeof(struct listnode));
    if(listset_lookup(this, item) == 1)
  {
    for(node = this->head; node != NULL; node = node->next)
    {
      if(strcmp(node->str,item)==0 && n == 0) // if head
      {
        this->head = node->next; 
        break;
      }
      if(strcmp(node->next->str,item)==0)
      {
        node->next = node->next->next;
        break;
      } 
      n=1;
      
    }
  }
    //if(deleted == false)
 // }

}
       /*struct listnode * temp;
        temp = malloc(sizeof(struct listnode));
        temp = node;*/
        //this->head = node->next;
        //free(temp);


        /*struct listnode * temp;
        temp = malloc(sizeof(struct listnode));
        temp = node->next;*/
        //node->next = node->next->next;
        //this->head = node->next;
        //free(temp);

         /*bool finished = false;
        while(finished == false)
        {
          node->next = node->next->next;
          if(node->next == NULL)
          {
            free(node);
            node = NULL;
            finished = true;
          }
          node = node->next;
        }*/


/* while(!node == NULL)
      {
        node-> str = node->next;
        this-> head = node;
        if(node->next == NULL)
        {
          node->str = NULL;
        }
        node = node->next; 
      }*/
  
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
		   struct listset * src2) {

         struct listnode * node1;
         node1 = malloc(sizeof(struct listnode));
         struct listnode * node2;
         node2 = malloc(sizeof(struct listnode));
         struct listnode * doi;
         doi = malloc(sizeof(struct listnode));
         for(node1 = dest->head; node1 != NULL; node1 = node1->next)
         {
           if(listset_lookup(dest, node1->str) == 0)
           {
             doi->str = node1->str;
             doi->next = dest->head;
             dest->head = node1;
            }
            for(node2 = dest->head; node2 != NULL; node2 = node2->next)
             {
                 if(listset_lookup(doi, node1->str) == 0)
                 {
                   doi->str = node1->str;
                   doi->next = dest->head;
                   dest->head = node1;
                }
              }
          }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
		       struct listset * src2) {

             struct listnode * node1;
             node1 = malloc(sizeof(struct listnode));
             struct listnode * node2;
             node2 = malloc(sizeof(struct listnode));
             struct listnode * doi;
             doi = malloc(sizeof(struct listnode));
             for(node1 = dest->head; node1 != NULL; node1 = node1->next)
             for(node2 = dest->head; node2 != NULL; node2 = node2->next)
             {
               if(strcmp(node1->str,node2->str)==0)
               {
                 if(listset_lookup(doi, node1->str) == 0)
                 {
                   doi->str = node1->str;
                   doi->next = dest->head;
                   dest->head = node1;
                  }
               }

             }

}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {

  int the_number_of_the_items=0;
  struct listnode * node;
  node = malloc(sizeof(struct listnode));
  for(node = this->head; node != NULL; node = node->next)
  {
    if(listset_lookup(this,node->str)==1)
    the_number_of_the_items++;
  }

  return the_number_of_the_items;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
