#include <stdio.h>
#include <ctype.h>
#include "StrList.h"

char* scanWord(){
        char* word = NULL;
        int size = 0;
        char input='\0';
         //Skip whitespace characters
        while (scanf("%c", &input) == 1 && isspace(input)){
            //do nothing
        }
        // Read the word
        while(!isspace(input)){
            word = realloc(word, (size + 1) * sizeof(char));
            if(word==NULL){
                free(word);
                return NULL;}
            word[size++] = input;

            // Read the next character
            if (scanf("%c", &input) != 1) {
                break;
            }
        }
        // Null-terminate the word
        word = realloc(word, (size + 1) * sizeof(char));
        if(word==NULL) {
            free(word);
            return NULL;
        }
        word[size] = '\0';

        return word;

}

void newList(StrList* theList){
    int size;
    char* word;
    scanf("%d", &size);
    for(int i=0; i<size; i++){
            word = scanWord();
            StrList_insertLast(theList, word);
    }
}


int main(){
    StrList* myList = StrList_alloc();
    int userInput=1;
    while(userInput != 0) {
       // printf("enter inp");
        scanf("%d", &userInput);

        if (userInput == 1) {
            newList(myList);
        }
        if (userInput == 2) {
            int index;
            scanf("%d",&index);
            char* word=scanWord();
            StrList_insertAt(myList,word,index);
            free(word);
        }
        if (userInput == 3) {
            StrList_print(myList);
        }
        if (userInput == 4) {
            printf("%d\n", StrList_size(myList));
        }
        if (userInput == 5) {
            int index=1;
            scanf("%d", &index);
            StrList_printAt(myList,index);
        }
        if (userInput == 6) {
            printf("%d\n", StrList_printLen(myList));
        }
        if (userInput == 7) {
            char* word=scanWord();
            int count=StrList_count(myList,word);
            printf("%d\n",count);
            free(word);
        }
        if (userInput == 8) {
            char* word=scanWord();
            StrList_remove(myList,word);
            free(word);
        }
        if (userInput == 9) {
            int index=1;
            scanf("%d", &index);
            StrList_removeAt(myList,index);
        }
        if (userInput == 10) {
            StrList_reverse(myList);
        }
        if (userInput == 11) {
            int size= StrList_size(myList);
            for(int i=size-1;i>=0;i--){
                StrList_removeAt(myList,i);
            }
        }
        if (userInput == 12) {
            StrList_sort(myList);
        }
        if (userInput == 13) {
            if(StrList_isSorted(myList)>0){
                printf("true\n");
            }
            else{
                printf("false\n");
            }
        }
        if (userInput == 0) {
            return 0;
        }
    }
    StrList_free(myList);
    return 0;
};


















//int main() {
//    // Create a new StrList
//    StrList* myList = StrList_alloc();
//
//    // Insert some elements
//    StrList_insertLast(myList, "apple");
//    StrList_insertLast(myList, "banana");
//    StrList_insertLast(myList, "orange");
//    StrList_insertLast(myList, "banana");
//    StrList_insertLast(myList, "cada");
//    StrList_insertLast(myList, "cara");
//    StrList_insertLast(myList, "data");
//    StrList_insertLast(myList, "10");
//    StrList_insertLast(myList, "11");
//    StrList_insertLast(myList, "2");
//    StrList_insertAt(myList,"second", 1);
//    // Print the list
//    printf("Original List: ");
//    StrList_print(myList);
//    printf("\n");
//
//    // Count occurrences of "banana"
//    //Wrong!! it give 4 instead of 2
//    printf("Occurrences of 'banana': %d\n", StrList_count(myList, "banana"));
//
//    // Remove all occurrences of "banana"
//    StrList_remove(myList, "banana");
//    printf("List after removing 'banana': ");
//    StrList_print(myList);
//    printf("\n");
//
//    // Sort the list
//    StrList_sort(myList);
//    printf("Sorted List: ");
//    StrList_print(myList);
//    StrList_reverse(myList);
//    printf("\n");
//    printf("reversed List: ");
//    StrList_print(myList);
//    printf("\n");
//
//    // Check if the list is sorted
//    printf("Is the list sorted? %s\n", StrList_isSorted(myList) ? "Yes" : "No");
//
//    // Free memory
//    StrList_free(myList);
//
//    return 0;
//}