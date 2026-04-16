/*  File  : linklist.c
 *  Desc  : File definisi untuk linkedlist lyra
 *  Type  : data structures container
 */

#include "../lyutils.h"


// // // STRUCT // // //


// Linked List model: Intrusive
typedef struct ___Ly_LinkedList{
  u8 amount;
  struct ___LLNode* node;
} Ly_LinkedList;

//
typedef struct ___LLNodes{
  struct ___Ly_LLNode* ptr;
} Ly_LinkedListNodes;


// // // IMPLEMENTATION // // //

//
void INIT_LY_LINKED_LIST(Ly_LinkedListNodes* ptr){}
