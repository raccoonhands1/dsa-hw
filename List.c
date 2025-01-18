#include <stdio.h>
#include <stdlib.h>
#include "List.h"
List *newList() {
    List *L = (List *)malloc(sizeof(List));
    if (L == NULL) {
        return NULL;
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}
void freeList(List **pL) {
    if (pL == NULL || *pL == NULL) {
        return;
    }
    List *L = *pL;
    Node *cur = L->front;
    while (cur != NULL) {
        Node *temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(L);
    *pL = NULL;
}
int length(List *L) {
    return L ? L->length : -1;
}
int index(List *L) {
    return L ? L->index : -1;
}
int front(List *L) {
    if (L && L->front) {
        return L->front->data;
    }
    return -1;
}
int back(List *L) {
    if (L && L->back) {
        return L->back->data;
    }
    return -1;
}
int get(List *L) {
    if (L == NULL || L->index < 0 || L->index >= L->length) {
        return -1;
    }
    return L->cursor ? L->cursor->data : -1;
}
bool equals(List *A, List *B) {
    if (A == NULL || B == NULL) return false;
    if (A->length != B->length) return false;
    Node *curA = A->front;
    Node *curB = B->front;
    while (curA != NULL && curB != NULL) {
        if (curA->data != curB->data) {
            return false;
        }
        curA = curA->next;
        curB = curB->next;
    }
    return true;
}
void set(List *L, int x) {
    if (L == NULL || L->index < 0 || L->index >= L->length) {
        return;
    }
    if (L->cursor) {
        L->cursor->data = x;
    }
}
void clear(List *L) {
    if (L == NULL) return;
    Node *cur = L->front;
    while (cur) {
        Node *temp = cur;
        cur = cur->next;
        free(temp);
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}
void moveFront(List *L) {
    if (L && L->front) {
        L->cursor = L->front;
        L->index = 0;
    }
}
void moveBack(List *L) {
    if (L && L->back) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}
void movePrev(List *L) {
    if (L && L->cursor && L->index > 0) {
        L->cursor = L->cursor->prev;
        L->index--;
    } else if (L && L->cursor && L->index == 0) {
        L->cursor = NULL;
        L->index = -1;
    }
}
void moveNext(List *L) {
    if (L && L->cursor && L->index < L->length - 1) {
        L->cursor = L->cursor->next;
        L->index++;
    } else if (L && L->cursor && L->index == L->length - 1) {
        L->cursor = NULL;
        L->index = -1;
    }
}
void prepend(List *L, int x) {
    if (L == NULL) return;
    Node *N = (Node *)malloc(sizeof(Node));
    N->data = x;
    N->next = L->front;
    N->prev = NULL;
    if (L->front) {
        L->front->prev = N;
    } else {
        L->back = N;
    }
    L->front = N;
    L->length++;
    if (L->index != -1) {
        L->index++;
    }
}
void append(List *L, int x) {
    if (L == NULL) return;
    Node *N = (Node *)malloc(sizeof(Node));
    N->data = x;
    N->next = NULL;
    N->prev = L->back;
    if (L->back) {
        L->back->next = N;
    } else {
        L->front = N;
    }
    L->back = N;
    L->length++;
}
void insertBefore(List *L, int x) {
    if (L == NULL || L-> length < 1 || L->index < 0) return;
    Node *N = (Node *)malloc(sizeof(Node));
    N->data = x;
    N->next = L->cursor;
    N->prev = L->cursor->prev;
    cursor->prev = N;
}
void insertAfter(List *L, int x) {
    if (L == NULL || L-> length < 1 || L->index < 0) return;
    Node *N = (Node *)malloc(sizeof(Node));
    N->data = x;
    N->prev = L->cursor;
    N->next = L->cursor->next;
    cursor->next = N;
}
void deleteFront(List *L) {
    if (L == NULL || L->length < 1) return;
    Node *temp = L->front;
    if (L->front == L->back) { 
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->front = L->front->next;
        L->front->prev = NULL;
        if (L->cursor == temp) {
            L->cursor = NULL;
            L->index = -1;
        } else if (L->index != -1) {
            L->index--;
        }
    }
    free(temp);
    L->length--;
}
void deleteBack(List *L) {
    if (L == NULL || L->length < 1) return;
    Node *temp = L->back;
    if (L->front == L->back) { 
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->back = L->back->prev;
        L->back->next = NULL;
        if (L->cursor == temp) {
            L->cursor = NULL;
            L->index = -1;
        }
    }
    free(temp);
    L->length--;
}
void delete(List *L) {
    if (L == NULL || L->length < 1 || L->cursor == NULL) return;
    Node *temp = L->cursor;
    if (L->front == L->back) {
        L->front = NULL;
        L->back = NULL;
    } else if (L->cursor == L->front) {
        L->front = L->front->next;
        L->front->prev = NULL;
    } else if (L->cursor == L->back) {
        L->back = L->back->prev;
        L->back->next = NULL;
    } else {
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
    }
    L->cursor = NULL;
    L->index = -1;
    free(temp);
    L->length--;
}
void printList(FILE *out, List *L) {
    if (L == NULL || out == NULL) {
        return;
    }
    Node *cur = L->front;
    while (cur != NULL) {
        fprintf(out, "%d ", cur->data);
        cur = cur->next;
    }
    fprintf(out, "\n");
}
List *copyList(List *L) {
    if (L == NULL) {
        return NULL;
    }
    List *newList = newList();
    if (newList == NULL) {
        return NULL;
    }
    Node *cur = L->front;
    while (cur != NULL) {
        append(newList, cur->data);
        cur = cur->next;
    }
}
List *concatList(List *A, List *B) {
    if (A == NULL || B == NULL) {
        return NULL;
    }
    List *newList = newList();
    if (newList == NULL) {
        return NULL;
    }
    Node *cur = A->front;
    while (cur != NULL) {
        append(newList, cur->data);
        cur = cur->next;
    }
    cur = B->front;
    while (cur != NULL) {
        append(newList, cur->data);
        cur = cur->next;
    }
    return newList;
}