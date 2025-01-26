#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Creates and returns a new empty List
List newList(void) {
    List L = malloc(sizeof(ListObj));
    if (L == NULL) {
        fprintf(stderr, "Memory allocation failed in newList.\n");
        exit(EXIT_FAILURE);
    }
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}

// Frees the memory associated with a List
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL); // Clear all nodes in the list
        free(*pL);  // Free the List object itself
        *pL = NULL; // Set the pointer to NULL
    }
}

// Returns the number of elements in the List
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "Error: length() called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// Returns the index of the cursor element, or -1 if undefined
int index(List L) {
    if (L == NULL) {
        fprintf(stderr, "Error: index() called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

// Returns the front element of the List
int front(List L) {
    if (L == NULL) {
        fprintf(stderr, "Error: front() called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "front called on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// Returns the back element of the List
int back(List L) {
    if (L == NULL) {
        fprintf(stderr, "back called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "back called on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// Returns the cursor element
int get(List L) {
    if (L == NULL) {
        fprintf(stderr, "get called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL || L->index < 0) {
        fprintf(stderr, "get called with undefined cursor.\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Checks if two Lists are equal
bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Error: equals() called on NULL list reference(s).\n");
        exit(EXIT_FAILURE);
    }
    if (A->length != B->length) {
        return false;
    }
    Node N = A->front;
    Node M = B->front;
    while (N != NULL) {
        if (N->data != M->data) {
            return false;
        }
        N = N->next;
        M = M->next;
    }
    return true;
}

// Clears all elements from the List
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "clear called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    while (L->front != NULL) {
        Node temp = L->front;
        L->front = L->front->next;
        free(temp);
    }
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

// Sets the cursor element to x
void set(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "Error: set() called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL || L->index < 0) {
        fprintf(stderr, "set called with undefined cursor.\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// Moves the cursor to the front of the List
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "moveFront called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

// Moves the cursor to the back of the List
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "Error: moveBack() called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

// Moves the cursor one step backward
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "movePrev called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        } else {
            L->cursor = L->cursor->prev;
            L->index--;
        }
    }
}

// Moves the cursor one step forward
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "moveNext called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        } else {
            L->cursor = L->cursor->next;
            L->index++;
        }
    }
}

// Prepends an element to the List
void prepend(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "prepend called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    Node N = malloc(sizeof(NodeObj));
    if (N == NULL) {
        fprintf(stderr, "Memory allocation failed in prepend.\n");
        exit(EXIT_FAILURE);
    }
    N->data = x;
    N->prev = NULL;
    N->next = L->front;

    if (L->length == 0) {
        L->front = L->back = N;
    } else {
        L->front->prev = N;
        L->front = N;
    }
    if (L->index >= 0) {
        L->index++;
    }
    L->length++;
}

// Appends an element to the List
void append(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "append called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    Node N = malloc(sizeof(NodeObj));
    if (N == NULL) {
        fprintf(stderr, "Memory allocation failed in append().\n");
        exit(EXIT_FAILURE);
    }
    N->data = x;
    N->next = NULL;
    N->prev = L->back;

    if (L->length == 0) {
        L->front = L->back = N;
    } else {
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

// Inserts an element before the cursor
void insertBefore(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "insertBefore called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL || L->index < 0) {
        fprintf(stderr, "cursor undefined.\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == L->front) {
        prepend(L, x);
    } else {
        Node N = malloc(sizeof(NodeObj));
        if (N == NULL) {
            fprintf(stderr, "Memory allocation failed in insertBefore.\n");
            exit(EXIT_FAILURE);
        }
        N->data = x;
        N->next = L->cursor;
        N->prev = L->cursor->prev;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
        L->length++;
        L->index++;
    }
}

// Inserts an element after the cursor
void insertAfter(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "insertAfter called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL || L->index < 0) {
        fprintf(stderr, "insertAfter called with undefined cursor.\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == L->back) {
        append(L, x);
    } else {
        Node N = malloc(sizeof(NodeObj));
        if (N == NULL) {
            fprintf(stderr, "Memory allocation failed in insertAfter.\n");
            exit(EXIT_FAILURE);
        }
        N->data = x;
        N->prev = L->cursor;
        N->next = L->cursor->next;
        L->cursor->next->prev = N;
        L->cursor->next = N;
        L->length++;
    }
}

// Deletes the front element of the List
void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "deleteFront called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "deleteFront called on an empty list.\n");
        exit(EXIT_FAILURE);
    }

    Node temp = L->front;
    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
    } else if (L->index > 0) {
        L->index--;
    }

    if (L->length == 1) {
        L->front = L->back = NULL;
    } else {
        L->front = L->front->next;
        L->front->prev = NULL;
    }

    free(temp);
    L->length--;
}

// Deletes the back element of the List
void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "deleteBack called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "deleteBack called on an empty list.\n");
        exit(EXIT_FAILURE);
    }

    Node temp = L->back;
    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }

    if (L->length == 1) {
        L->front = L->back = NULL;
    } else {
        L->back = L->back->prev;
        L->back->next = NULL;
    }

    free(temp);
    L->length--;
}

// Deletes the cursor element
void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "delete called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL || L->index < 0) {
        fprintf(stderr, "delete called with undef cursor.\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == L->front) {
        deleteFront(L);
    } else if (L->cursor == L->back) {
        deleteBack(L);
    } else {
        Node temp = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        L->cursor = NULL;
        L->index = -1;
        free(temp);
        L->length--;
    }
}

// Prints the List to a file
void printList(FILE* out, List L) {
    if (L == NULL) {
        fprintf(stderr, "printList called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    Node N = L->front;
    while (N != NULL) {
        fprintf(out, "%d ", N->data);
        N = N->next;
    }
}

// Returns a copy of the List
List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "copyList called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    List copy = newList();
    Node N = L->front;
    while (N != NULL) {
        append(copy, N->data);
        N = N->next;
    }
    return copy;
}

// Concatenates two Lists
List concatList(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "concatList called on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }
    List concat = copyList(A);
    Node N = B->front;
    while (N != NULL) {
        append(concat, N->data);
        N = N->next;
    }
    return concat;
}