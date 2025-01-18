#ifndef List_h
#define List_h
#include <stdbool.h>

typedef struct List {
    int value;
    struct List *next;
} List;

List newList(void); // Creates and returns a new empty List.
void freeList(List* pL); // Frees all heap memory associated with *pL, and sets
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
int front(List L); // Returns front element of L. Pre: length()>0
int back(List L); // Returns back element of L. Pre: length()>0
int get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0
bool equals(List A, List B); // Returns true iff Lists A and B contain the same
void clear(List L); // Resets L to its original empty state.
void set(List L, int x); // Overwrites the cursor element’s data with x.
void moveFront(List L); // If L is non-empty, sets cursor under the front element,
void moveBack(List L); // If L is non-empty, sets cursor under the back element,
void movePrev(List L); // If cursor is defined and not at front, move cursor one
void moveNext(List L); // If cursor is defined and not at back, move cursor one
void prepend(List L, int x); // Insert new element into L. If L is non-empty,
void append(List L, int x); // Insert new element into L. If L is non-empty,
void insertBefore(List L, int x); // Insert new element before cursor.
void insertAfter(List L, int x); // Insert new element after cursor.
void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete(List L); // Delete cursor element, making cursor undefined.
void printList(FILE* out, List L); // Prints to the file pointed to by out, a
List copyList(List L); // Returns a new List representing the same integer
#endif
