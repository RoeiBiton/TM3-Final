#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Node & List Data Structures
typedef struct _node {
    char* _data;
    struct _node * _next;
} Node;

typedef struct _StrList {
    Node* _head;
    size_t _size;
}StrList;


//------------------------------------------------
// Node implementation
//------------------------------------------------

Node* Node_alloc(char* data, Node* next) {
    Node *p = (Node *) malloc(sizeof(Node));
    if (p != NULL) {
        p->_data = data;
        p->_next = next;
    }
    return p;
}

void Node_free(Node* node) {
    if(node!=NULL) {
        free(node);
    }
}
//------------------------------------------------



//------------------------------------------------
// StrList implementation
//------------------------------------------------

StrList* StrList_alloc() {
    StrList* p= (StrList*)malloc(sizeof(StrList));
    p->_head= NULL;
    p->_size= 0;
    return p;
}

void StrList_free(StrList* StrList) {
    if (StrList==NULL) return;
    Node* p1= StrList->_head;
    Node* p2;
    while(p1!=NULL) {
        p2= p1;
        p1= p1->_next;
        Node_free(p2);
    }
    free(StrList);
}

size_t StrList_size(const StrList* StrList) {
    return StrList->_size;
}

Node* getNodeAt(const StrList* StrList, int index){
    if(StrList==NULL || index<0){return NULL;}
    if(StrList->_size<index+1){return NULL;}
    Node* p1= StrList->_head;
    if(index==0){return p1;}
    else {
        for (int i = 1; i <= index; i++) {
            p1 = p1->_next;
        }
    }
    return p1;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    Node* newNode= Node_alloc(strdup(data), NULL);
    Node* lastNode= getNodeAt(StrList,(int)StrList->_size-1);
    if(lastNode==NULL){
        StrList->_head = newNode;
    }
    else{
        lastNode->_next=newNode;
    }
    StrList->_size++;
}

void StrList_insertAt(StrList* StrList, const char* data,int index){
    if (index < 0 || StrList->_size<index+1){return;}
    Node* newNode= Node_alloc(strdup(data), NULL);
    Node* p1 = getNodeAt(StrList, index);
    if(index==0){
        newNode->_next=p1;
        StrList->_head=newNode;
    }
    else{
        Node* p0 = getNodeAt(StrList, index-1);
        newNode->_next=p1;
        p0->_next=newNode;
    }
    StrList->_size++;

}

char* StrList_firstData(const StrList* StrList) {
    Node *head = StrList->_head;
    if (head == NULL) { return NULL; }
    return head->_data;
}
/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList) {
    Node *p = StrList->_head;
    if(p==NULL){printf("isNULL");}
    while (p != NULL) {
        printf("%s", p->_data);
        if (p->_next != NULL) {
            printf(" ");
        }
        p = p->_next;
    }
    printf("\n");
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* Strlist,int index) {
    if (Strlist != NULL && index >= 0) {
        if (index <= (Strlist->_size) - 1) {
            Node *p = getNodeAt(Strlist, index);
            printf("%s\n", p->_data);
        }
    }
}
/*
 * Return the amount of chars in the list.
*/
//check if -1 or 0
int StrList_printLen(const StrList* Strlist){
    if(Strlist==NULL){return -1;}
    int len= 0;
    Node* p0 =Strlist->_head;
    for(int i=0; i<Strlist->_size;i++){
        len= len+ strlen(p0->_data);
        p0=p0->_next;
    }
    return len;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* StrList, const char* data) {
    int counter = 0;
    if (StrList == NULL || data == NULL) { return -1;}
    Node *p0 = StrList->_head;
    for(int i=0; i<StrList->_size; i++) {
        int cmp = strcmp(p0->_data, data);
        if (cmp == 0) {
            counter++;
        }
        p0=p0->_next;
    }
    return counter;
}
/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) { return; }
    Node* p0 = StrList->_head;
    int cmp= strcmp(p0->_data,data);
    if(cmp==0){
        if(p0->_next==NULL) {
            StrList_free(StrList);
            return;
        }
        else{
            StrList->_head=p0->_next;
            Node_free(p0);
        }
    }
    else{
        for(int i=1; i<StrList->_size;i++){
            Node* p1= getNodeAt(StrList,i);
            int cmp= strcmp(p1->_data,data);
            if(cmp==0){
                Node* prev= getNodeAt(StrList,i-1);
                prev->_next=p1->_next;
                Node_free(p1);
                StrList->_size--;
                i--;
            }
        }
    }
}


/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index) {
    if (StrList == NULL || index < 0) { return; }
    if (index == 0) {
        Node* head= StrList->_head;
        StrList->_head = (StrList->_head)->_next;
        Node_free(head);
        StrList->_size--;
    }
    if (index  < StrList->_size) {
        Node *p1 = getNodeAt(StrList, index - 1);
        Node *p2 = getNodeAt(StrList, index + 1);
        Node *t = getNodeAt(StrList, index);
        if (p2 == NULL) {
            p1->_next = NULL;
            Node_free(t);
        } else {
            p1->_next = p2;
            Node_free(t);
        }
    }
    StrList->_size--;
}
/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    int ans=1;
    if(StrList1->_size!=StrList2->_size){return 0;}
    if(StrList1==NULL && StrList2==NULL){return 1;}
    Node* p1 = StrList1->_head;
    Node* p2 = StrList2->_head;
    for(int i=0; i<StrList1->_size;i++){
        int cmp = strcmp(p1->_data,p2->_data);
        if(cmp!=0){
            ans=0;
            return ans;
        }
        p1=p1->_next;
        p2=p2->_next;
    }
    return ans;
}

/*
 * Clones the given StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* StrList) {
    if (StrList == NULL) { return NULL; }
    struct _StrList *cloneList = (struct _StrList *) StrList_alloc();
    for (int i = 0; i < StrList->_size; i++) {
        Node *clone = getNodeAt(StrList, i);
        char *data = strdup(clone->_data);
        StrList_insertLast((struct _StrList *) cloneList, data);
    }
    return (struct _StrList*) cloneList;
}
/*
 * Reverces the given StrList.
 */
void StrList_reverse( StrList* StrList){
    struct _StrList* cloneList = (struct _StrList *) StrList_alloc();
    cloneList = StrList_clone(StrList);
    StrList->_head->_data= getNodeAt(cloneList,cloneList->_size-1)->_data;
    for(int i=cloneList->_size-1;i>=0;i--){
        getNodeAt(StrList, StrList_size(StrList)-1-i)->_data= getNodeAt(cloneList,i)->_data;
    }
}

/*
 * Sort the given list in lexicographical order
 */
void StrList_sort( StrList* StrList) {
    if (StrList == NULL) { return; }
    if(StrList->_size==1){return;}
    for(int i=0; i<StrList->_size-1;i++) {
        for (int j = 0; j < StrList->_size - i - 1; j++) {
            Node* p1 = getNodeAt(StrList,j);
            Node* p2 = getNodeAt(StrList,j+1);
            if(strcmp(p1->_data,p2->_data)>0) {
                char *temp = p1->_data;
                p1->_data = p2->_data;
                p2->_data = temp;
            }
            }
        }
    }

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL) { return 1; }
    Node* p0 = StrList->_head;
    for(int i =0; i<StrList->_size-1; i++){
        int cmp=strcmp(p0->_data,(p0->_next)->_data);
        if(cmp>0){return 0;}
        p0=p0->_next;
    }
    return 1;
}

//------------------------------------------------
