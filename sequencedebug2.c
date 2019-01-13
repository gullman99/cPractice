#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
#include <stdio.h>
#include <stdlib.h>

//contructs a linked list with contructor and functions

//sequence debug 2


typedef struct linkedList {
  int value;
  struct linkedList *next;
} linkedListStruct;

struct linkedList *linkedListConstruct(int *value, int listSize) {
  struct linkedList *headPtr;
  struct linkedList *tempPtr;
  headPtr = malloc(sizeof(struct linkedList));

  if (listSize == 1) {
    headPtr->value = *value;
    headPtr->next = NULL;
  }
  else {
    tempPtr = headPtr;
    for (int i = 0; i < listSize; i++) {
      tempPtr->value = value[i];
      tempPtr->next = malloc(sizeof(struct linkedList));
      tempPtr = tempPtr->next;
    }
    tempPtr->next = NULL;
  }
  return headPtr;
}

void linkedListAdd(int value, struct linkedList *headPtr) {
  struct linkedList *currPtr;
  struct linkedList *prevPtr;
  currPtr = headPtr;
  while (currPtr != NULL) { /// traverse to end of linked list
    prevPtr = currPtr;
    currPtr = currPtr->next;
  }
  currPtr = malloc(sizeof(struct linkedList));
  prevPtr->next = currPtr;
  currPtr->value = value;
  currPtr->next = NULL;
}

void linkedListPrint(struct linkedList *headPtr) {
  struct linkedList *currPtr;
  struct linkedList *prevPtr;
  currPtr = headPtr;
  while (currPtr != NULL) { /// traverse to end of linked list
    printf("%d ", currPtr->value);
    prevPtr = currPtr;
    currPtr = currPtr->next;
  }

  printf("\n");
}

int linkedListSize(struct linkedList *headPtr) {
  struct linkedList *currPtr;
  struct linkedList *prevPtr;
  currPtr = headPtr;
  int size=0;

  while (currPtr != NULL) { /// traverse to end of linked list
    size++;
    prevPtr = currPtr;
    currPtr = currPtr->next;
  }
  return size;
}

int linkedListAccessValue(int index, struct linkedList *headPtr){
  struct linkedList *currPtr;
  struct linkedList *prevPtr;
  currPtr = headPtr;
  int value,i = 0;

  while (currPtr != NULL && i<index) { /// traverse to index of linked list
    prevPtr = currPtr;
    currPtr = currPtr->next;
  }
  return currPtr->value;
}

// Complete the dynamicArray function below.


/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */

int* dynamicArray(int n, int queries_rows, int queries_columns, int queries[5][3], int* result_count) {
  int seqSize =0; 
  int linkListIndex=0;
  struct linkedList * sequenceArr[n];
  int lastAnswer=0;

  for (int k = 0; k < n; k++) {
    sequenceArr[k] = linkedListConstruct(&lastAnswer, 1);
  }

  for (int i = 0; i < queries_rows; i++) {
    int seqIndex, x, y;
    x=queries[i][1];
    y=queries[i][2];
    if (queries[i][0] == 1){// Query type 1
        seqIndex=((x^lastAnswer)%n);
        if(linkedListSize(sequenceArr[seqIndex])==1){
          sequenceArr[seqIndex]->value = y;
        }
        else{
          linkedListAdd(y,sequenceArr[seqIndex]);    
        }
    }
    else{
        seqIndex=((x^lastAnswer)%n);
        seqSize=linkedListSize(sequenceArr[n]);
        linkListIndex = y%seqSize;
        lastAnswer=linkedListAccessValue(linkListIndex,sequenceArr[n]);
        printf("%d\n",lastAnswer);
    }
  }
}

int main(){
    int queries[5][3]={
{1, 0, 5},
{1, 1, 7},
{1, 0, 3},
{2, 1, 0},
{2, 1, 1}};

int n=2;
int queries_rows=5;
int queries_columns=3;
dynamicArray(n, queries_rows, queries_columns, queries, 0);



return 0;
}





/*int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nq = split_string(rtrim(readline()));

    char* n_endptr;
    char* n_str = nq[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* q_endptr;
    char* q_str = nq[1];
    int q = strtol(q_str, &q_endptr, 10);

    if (q_endptr == q_str || *q_endptr != '\0') { exit(EXIT_FAILURE); }

    int** queries = malloc(q * sizeof(int*));

    for (int i = 0; i < q; i++) {
        *(queries + i) = malloc(3 * (sizeof(int)));

        char** queries_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 3; j++) {
            char* queries_item_endptr;
            char* queries_item_str = *(queries_item_temp + j);
            int queries_item = strtol(queries_item_str, &queries_item_endptr, 10);

            if (queries_item_endptr == queries_item_str || *queries_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(queries + i) + j) = queries_item;
        }
    }

    int queries_rows = q;
    int queries_columns = 3;

    int result_count;
    int* result = dynamicArray(n, queries_rows, queries_columns, queries, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
*/
