#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct linkedList{    
    int value;
    struct linkedList * next;
}linkedListStruct;

struct linkedList * linkedListConstruct(int * value, int listSize){
  struct linkedList *headPtr;
  struct linkedList *tempPtr;
  headPtr = malloc(sizeof(struct linkedList));

  if (listSize == 1) {
    headPtr->value=*value;
    headPtr->next=NULL;
  }
  else{    
    tempPtr = headPtr;
    for(int i=0; i<listSize; i++){
        tempPtr->value = value[i];
        tempPtr->next = malloc(sizeof(struct linkedList));
        tempPtr = tempPtr->next;
    }
    tempPtr->next = NULL;
  }  
    return headPtr;
}

void linkedListAdd(int value, struct linkedList * headPtr) {
  struct linkedList * currPtr;
  struct linkedList * prevPtr;
  currPtr = headPtr;
  while(currPtr != NULL){     ///traverse to end of linked list
    prevPtr = currPtr;
    currPtr = currPtr->next;
  }
  currPtr=malloc(sizeof(struct linkedList));
 prevPtr->next = currPtr;
 currPtr->value = value;
 currPtr->next = NULL;
}

void linkedListPrint(struct linkedList * headPtr){
  struct linkedList * currPtr;
  struct linkedList * prevPtr;
  currPtr = headPtr;
  while(currPtr != NULL){     ///traverse to end of linked list
    printf("%d ", currPtr->value);
    prevPtr = currPtr;
    currPtr = currPtr->next;
  }

  printf("\n");
}



int main(){
    int one = 1;
    struct linkedList * headPtr;
    headPtr = linkedListConstruct(&one, 1);
    linkedListAdd(2, headPtr);
    linkedListPrint(headPtr);
    return 0;
}



