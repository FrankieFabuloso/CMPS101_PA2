/*-----------------------------------------------------------------------------
 * List.c
 *
 * Name: Francisco Rocha
 * User ID: frocha
 * Program name: pa2
 * Source code: Professor Tantalo
 *
*///---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include"List.h"


// private types and functions ------------------------------------------------

// NodeObj
typedef struct NodeObj{
   int data;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor for private Node type
Node newNode(int x) {
   Node N = malloc(sizeof(NodeObj));
   N->data = x;
   N->prev = N->next = NULL;
   return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// ListObj
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// List
// Exported reference type
typedef struct ListObj* List;

// Constructors-Destructors --------------------------------------------------- 

// newList()
// constructor for the List type
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	assert(L!=NULL);
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return (L);
}

// freeList()
// destructor for the List type
void freeList(List* p){
   if( p!=NULL && *p!=NULL ){
      while( !isEmpty(*p) ){
       	deleteBack(*p); //empty the List
   }
      free(*p);
      *p = NULL;
   }
}


// Access functions ----------------------------------------------------------- 
// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(List L){
	if( L==NULL ){
		fprintf(stderr, 
			"List Error: calling isEmpty() on NULL List reference\n");
		exit(1);
	}
   return(L->length==0);
}

// length()
// returns the length of the List
// pre: none
int length(List L){
	if (L==NULL){
		fprintf(stderr,
			"List Error: calling length() on NUll List reference\n");
		exit(1);
	}
	return(L->length);
}

// getIndex()
// retruns the location of the cursor
// pre: none
int getIndex(List L){
	if (L==NULL){
		fprintf(stderr,
			"List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->index);
}

// front()
// returns the front element of this List
// pre: length()>0
int front(List L){
	if(isEmpty(L)){
		fprintf(stderr, 
			"List Error: calling front() on NULL List reference");
		exit(1);
	}
	return L->front->data;
}

// back()
// returns the back element of this List
// pre: length()>0
int back(List L){
	if(L==NULL){
		fprintf(stderr, 
			"List Error: calling back() on NULL List reference");
		exit(1);
	}
	return L->back->data;	
}

// getElement()
// returns the element at which the cursor is pointing to
// pre:
int getElement(List L){
	if(L==NULL){
		fprintf(stderr, 
			"List Error: calling getElement) on NULL List reference");
		exit(1);
	}
	if(getIndex(L) < 0){
		fprintf(stderr, 
			"List Error: calling getElement() on out of bounds cursor reference");
		exit(1);
	}
	if(getIndex(L) == 0) { 
		return back(L);
	}else{
		return L->cursor->data;
	}
}

// equals()
// returns 1 if the two lists equal, 0 if they dont
// pre: none
int equals(List A, List B){
	int flag = 1;
	Node N = NULL;
	Node M = NULL;
	N = A->front;
	M = B->front;
	if(length(A) == length(B)){
		while(flag && N!=NULL){
			flag = (N->data == M->data);
			N = N->next;
			M = M->next;
		}
		return flag;
	}else{
		return 0;
	}
}
// Manipulation procedures ----------------------------------------------------
// clear()
// pre: none
void clear(List L){
	while(L->length > 0){
		deleteBack(L);
	}
}
// moveTo()
// moves cursor to index wanted (givesn by i)
// pre: none
void moveTo(List L, int i){
	L->index = i;
	L->cursor = L->back;
	int j;

	for(j=0; j<i; j++){
		if(L->cursor->next == NULL){
			L->index = -1;
			return;
		}else{
			L->cursor = L->cursor->next;
		}
	}
}
// movePrev()
// moves cursor towards the back of the List
// pre: none
void movePrev(List L){
	if(L->cursor->prev == NULL ){
		L->index = -1;
	}else{
		moveTo(L, getIndex(L)-1);
	}
}

// moveNext()
// moves cursor towards the front of the List
// pre: none
void moveNext(List L){
	if(L->cursor == NULL || L->index == -1){
		L->index = -1;
	}else{
		moveTo(L, getIndex(L)+1);
	}
}

// prepend()
// adds data to the back of this List
// pre: none
void prepend(List L, int data){
	Node N = NULL;
	N = newNode(data);
	if(isEmpty(L)){
		L->front = L->back = N;
		L->index = 0;
	}else{
		N->next = L->back;
		L->back->prev = N;
		L->back = N;
		L->cursor = L->back;
	}
	L->length++;
}
// append()
// adds data to the begining of this List
// pre: none
void append(List L, int data){
	Node N = NULL;
	N = newNode(data);
	if(isEmpty(L)){
		L->front = L->back = N;
		L->index = 0;
	}else{
		N->prev = L->front;
		L->front->next = N;
		L->front = N;
	}
	L->length++;
}

// insertBefore()
// adds new element before the cursor
// pre: length()>0, getIndex()>=0
void insertBefore(List L, int data){
	Node before = NULL;
	Node N = newNode(data);
	if(L==NULL){
		fprintf(stderr, 
			"List Error: calling insertBefore() on NULL List reference");
		exit(1);
	}
	if(getIndex(L) < 0){
		fprintf(stderr, 
			"List Error: calling insertBefore() on undefined cusor reference");
		exit(1);
	}
	if(getIndex(L)==0){
		prepend(L, data);
		return;
	}
	before = L->cursor->prev;
	before->next = N;
	N->prev = before;
	N->next = L->cursor;
	L->cursor->prev = N;
	L->length++;
}

// insterAfter()
// inserts new element after cursor in this List
// pre: length()>0, getIndex()>=0
void insertAfter(List L, int data){
	Node after = NULL;
	Node N = newNode(data);
	if(L==NULL){
		fprintf(stderr, 
			"List Error: calling insertAfter() on NULL List reference");
		exit(1);
	}
	if(getIndex(L) < 0){
		fprintf(stderr, 
			"List Error: calling insertAfter() on undefined cusor reference");
		exit(1);
	}
	if(getIndex(L)==0){
		append(L, data);
		return;
	}
	after = L->cursor->next;
	after->prev = N;
	N->next = after;
	N->prev = L->cursor;
	L->cursor->next = N;
	L->length++;
}

// deleteFront()
// deletes the front element of the List
// pre: length()>0
void deleteFront(List L){
	Node N = NULL;
	if(L==NULL){
		fprintf(stderr, 
			"List Error: calling deleteFront() on NULL List reference");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling deleteFront() on empty List\n" );
		exit(1);
	}
	N = L->front;
	if(L->length <= 1){
		L->front = L->back = L->cursor = NULL;
		L->index = -1;
		L->length = 0;
	}else{
		L->front = L->front->prev;
		L->front->next = NULL;
		N->prev = NULL;
		L->length--;
	}
	freeNode(&N);
}
// deleteBack()
// deletes the bacl of the list
// pre: length()>0
void deleteBack(List L){
	Node N = NULL;
	if(L==NULL){
		fprintf(stderr, 
			"List Error: calling deleteBack() on NULL List reference");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling deleteBack on empty Queue\n" );
		exit(1);
	}
	N = L->back;
	if(L->length == 1){
		L->back = L->front = L->cursor = NULL;
		L->index = -1;
		L->length = 0;
	}else{
	L->back = L->back->next;
	L->back->prev = NULL;
	N->next = NULL;
	L->length--;
	}	
	freeNode(&N);
}
// delete()
// delets cursor element in this list. Cursor is undefines after this op.
// pre: length()>0, getIndex()>=0
void delete(List L){
	Node F = NULL;
	Node B = NULL;
	Node N = NULL;
	if(L==NULL){
		fprintf(stderr, 
			"List Error: calling delete() on NULL List reference");
		exit(1);
	}
	if(getIndex(L) < 0){
		fprintf(stderr, 
			"List Error: calling delete() on undefined pointer");
		exit(1);
	}
	if(getIndex(L) == 0){
		deleteBack(L);
		return;
	}
	if(getIndex(L) == L->length-1){
		deleteFront(L);
		return;
	}
	N = L->cursor;
	F = L->cursor->next;
	B = L->cursor->prev;
	L->cursor->prev = NULL;
	L->cursor->next = NULL;
	L->cursor = NULL;
	B->next = F;
	F->prev = B;
	L->index = -1;
	L->length--;
	freeNode(&N);
}
// Other operations ----------------------------------------------------------- 
void printList(FILE* out, List L){
	Node N = NULL;
	if( L==NULL){
		fprintf(stderr, 
			"List Error: calling printStack() on NUll List reference\n" );
		exit(1);
	}
	for(N=L->back; N!=NULL; N=N->next) fprintf(out, "%d ", N->data);
	fprintf(out, "\n");
}

List copyList(List L){
	List Q = newList();
	Node N = L->back;

	while(N!=NULL){
		append(Q, N->data);
		N = N->next;
	}
	Q->index = -1;
	return Q;
}


