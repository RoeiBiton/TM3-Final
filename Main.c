#include <stdio.h>
#include <ctype.h>
#include "StrList.h"

/*
   Function: scanWord
   -------------------
   Scans input characters and extracts a word.

   Returns:
   - A dynamically allocated string containing the scanned word.
   - NULL if memory allocation fails or no word is scanned.
*/

char* scanWord(){
        char* word = NULL;
        int size = 0;
        char input='\0';
         // Skip leading whitespace characters
        while (scanf("%c", &input) == 1 && isspace(input)){
            //do nothing
        }
         // Scan characters until whitespace is encountered
        while(!isspace(input)){
            word = realloc(word, (size + 1) * sizeof(char));
            if(word==NULL){
                free(word);
                return NULL;}
            word[size++] = input;

            // Check if another character can be scanned
            if (scanf("%c", &input) != 1) {
                break;
            }
        }
           // Allocate space for null terminator
        word = realloc(word, (size + 1) * sizeof(char));
        if(word==NULL) {
            free(word);
            return NULL;
        }
        word[size] = '\0';

        return word;

}

/*
   Function: newList
   -----------------
   Creates a new list and populates it with words entered by the user.

   Parameters:
   - theList: Pointer to a StrList object where the words will be stored.
*/

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
