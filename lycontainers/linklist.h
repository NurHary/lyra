#ifndef LINKLIST
#define LINKLIST

//
//
//
//
//
//

// // // STRUCT // // //

// Linked List Used to contain dynamic amount of items
//  
// For Example
// `Ly_LinkedList bokep;`
typedef struct ___Ly_LinkedList Ly_LinkedList;
typedef struct ___Ly_LLNodes Ly_LinkedListNodes;

// // // IMPLEMENTATION // // //
void INIT_LY_LINKED_LIST(Ly_LinkedListNodes* ptr);
void ly_linkedlist_connect(Ly_LinkedListNodes* ptr, Ly_LinkedList* rhs);
void ly_linkedlist_();


#endif
