//www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define DATA_MAX_SIZE 24
#define DATA_MAX_LENGTH 10000

struct node {
    int dataCtr;
   char text[DATA_MAX_SIZE];
    int value[DATA_MAX_SIZE];
    struct node *back;
   struct node *next;
};

int ListSize = 0;
struct node *head = NULL;
struct node *tail = NULL;
int ListSizeOut = 0;
struct node *headOut = NULL;
struct node *tailOut = NULL;

const char *word_find(const char *str, const char *word) {
    const char *p = NULL;
    size_t len = strlen(word);

    if (len > 0) {
        for (p = str; (p = strstr(p, word)) != NULL; p++) {
            if (p == str || !isalnum((unsigned char)p[-1])) {
                if (!isalnum((unsigned char)p[len]))
                    break;  /* we have a match! */
                p += len;   /* next match is at least len+1 bytes away */
            }
        }
    }
    return p;
} // Obtained from stackoverflow www.stackoverflow.com/questions/42352846/matching-an-exact-word-using-in-c

//display the list
void printList(struct node *ptr) {
   //start from the beginning

   while(ptr != NULL) {
       for(int i = 0; i < ptr->dataCtr; i++){
           printf("%c: %d ", ptr->text[i], ptr->value[i]);
       }
      printf("\n");
      ptr = ptr->next;
   }
    printf("\n");
}

void printFilter(struct node *ptr, char dataPrint[], int ctr ){
    bool found = false;
    while(ptr != NULL) {
        for(int i = 0; i < ptr->dataCtr; i++){
            for(int j = 0; j < ctr; j++){
                if(ptr->text[i] == dataPrint[j]){
                    printf("%c: %d ", ptr->text[i], ptr->value[i]);
                    found = true;
                }
            }
        }
        if (found == true)
        {
            printf("\n");
            found = false;
        }
       ptr = ptr->next;
    }
    printf("\n");
}

void deleteNode(struct node *ptr){
    if (ptr == headOut && ptr == tailOut){
        headOut = NULL;
        tailOut = NULL;
    }
    else if(ptr == headOut){
        ptr->next->back = NULL;
        headOut = ptr->next;
    }
    else if (ptr == tailOut){
        tailOut = ptr->back;
        ptr->back->next = NULL;
    }
    else{
        ptr->back->next = ptr->next;
        ptr->next->back = ptr->back; //change the back pointer
    }
}

void securityFilter(int securityValue){
    struct node *ptr = headOut;
    
    while(ptr != NULL){
        for(int i = 0 ; i < ptr->dataCtr; i++){
            if (ptr->text[i] == 'Y' && ptr->value[i] > securityValue){
                //Later on create a function to actually free the allocated memory
                deleteNode(ptr);
                ListSizeOut--;
                break;
            }
        }
        ptr = ptr->next;
    }
}

void compFilter(char dataName, char compOp, int dataValue ){
    struct node *ptr = headOut;
    bool found;
    
    if (dataName == 'Z') { return;}
    
    while(ptr != NULL){
        found = false;
        for(int i = 0 ; i < ptr->dataCtr; i++){
            if (ptr->text[i] == dataName){
                found = true;
                if (compOp == '>' && ptr->value[i] > dataValue){

                    break;
                }
                else if (compOp == '=' && ptr->value[i] == dataValue){
                    break;
                }
                else if (compOp == '<' && ptr->value[i] < dataValue){

                    break;
                }
                else{
                    //Later on create a function to actually free the allocated memory
                    deleteNode(ptr);
                }
            }
        }
        if (found == false){
            deleteNode(ptr);
        }
        ptr = ptr->next;
    }
}

//insert link at the last location
void insert(char tmpChar[], int tmpInt[], int ctr) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
    link->next = NULL;
    link->back = NULL;
    
    link->dataCtr = ctr;
    for(int i =0; i < ctr; i++){
        link->text[i] = tmpChar[i];
        link->value[i] = tmpInt[i];
    }
    
    if (head == NULL)
    {
        head = link;
        tail = link;
    }
    else
    {
        tail->next = link;
        link->back = tail;
        tail = link;
    }
    ListSize++;
}

struct node *copy(void){
    ListSizeOut = ListSize;
    struct node *headRt = NULL;
    tailOut = NULL;
    struct node *ptr = head;
    
    while(ptr != NULL) {
        struct node *link = (struct node*) malloc(sizeof(struct node));
        link->dataCtr = ptr->dataCtr;
        link->next = NULL;
        link->back = NULL;
        
        for(int i = 0; i < ptr->dataCtr; i++){
            
            link->text[i] = ptr->text[i];
            link->value[i] = ptr->value[i];

        }
    
        if (headRt == NULL)
        {
            headRt = link;
            tailOut = headRt;
        }
        else
        {
            tailOut->next = link;
            link->back = tailOut;
            tailOut = link;
        }
        ptr = ptr->next;
    }
    return headRt;
}
//Function obtained from Geeks for Geeks www.geeksforgeeks.org/insertion-sort/
void insertionSort(int arr[], struct node* ptr[], int n)
{
    int i, key, j;
    struct node *key2;
    for (i = 1; i < n; i++) {
        
        key = arr[i];
        key2 = ptr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            ptr[j + 1] = ptr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        ptr[j + 1] = key2;
    }
}
void sortList(char dataName, int printInst){
    struct node *ptr = headOut;
    struct node *parN[ListSizeOut];
     int parV[ListSizeOut];

    int ctr = 0;
    while(ptr != NULL){
        for(int i = 0 ; i < ptr->dataCtr; i++){
            if (ptr->text[i] == dataName){
                parN[ctr] = ptr;
                parV[ctr] = ptr->value[i];
                ctr++;
                break;
            }
        }
        ptr = ptr->next;
    }
    insertionSort(parV, parN, ctr);
    
    struct node *temp = NULL;
    headOut = NULL;
    
    if(printInst == 1){
        for(int i = 0; i < ctr; i++){
            if(i == 0 ){
                temp = parN[i];
                temp->back = NULL;
                temp->next = NULL;
                headOut = temp;
            }
            else{
                temp->next = parN[i];
                temp = parN[i];
                temp->back = parN[i-1];
                temp->next = NULL;
                        
            }
        }
    }
    else if(printInst == -1){
        for(int i = ctr-1; i >= 0; i--){
            if(i == ctr - 1 ){
                temp = parN[i];
                temp->back = NULL;
                temp->next = NULL;
                headOut = temp;
            }
            else{
                temp->next = parN[i];
                temp = parN[i];
                temp->back = parN[i+1];
                temp->next = NULL;
            }
        }
    }
}

int main(int argc, char**argv)
{
    //open file data.txt
    FILE *fp;
    fp = fopen("data.txt","r");
    if(fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    //read data in file data.txt
    char tmpChar[DATA_MAX_SIZE];
    int tmpInt[DATA_MAX_SIZE];
    char *textTemp = (char*)malloc(DATA_MAX_LENGTH);
    
    int idx = 1;    //Keeps track of query number
    int ctr = 1;    //Keeps track of amount of values within a line - out of 23 possible values
    while(fgets(textTemp, DATA_MAX_LENGTH,fp ) != NULL){    //Gets each line from the data.txt
        ctr = 1;
        int stringPos = 0;  //Keeps track of position within each string line so that multiple values can be read;
        tmpChar[0] = 'A';
        tmpInt[0] = idx;
        while(sscanf(textTemp, " %c%*s%d%n", &tmpChar[ctr], &tmpInt[ctr], &stringPos) ==  2){
            textTemp += stringPos;
            ctr++;
        }
        insert(tmpChar, tmpInt, ctr); //Insert array into table
        idx++;
    }
    fclose(fp);
    
    //read query from final.txt
    fp = fopen("final.txt","r");
    if(fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    char charData;
    char operationData[4];
    char operatorV;
    int intData;
    int queryCtr = 1;
    
    bool queryBool = false;
    while(fgets(textTemp, DATA_MAX_LENGTH, fp) != NULL){    //Gets each line from the final.txt
        headOut = copy();  //make a copy of the linked list
        intData = 0;
        
        sscanf(textTemp, " %4s %*s %d", operationData, &intData);

        if (intData != 0){
            securityFilter(intData);
        }
       
        if(strcmp(operationData, "FIND") == 0){ //FIND
            printf("%s", textTemp);
            do {
                fgets(textTemp, DATA_MAX_LENGTH, fp);
                if(strstr(textTemp, ";") != NULL){
                    
                    printf("//Query%d\n", queryCtr);
                    
                    if(strstr(textTemp, "X") != NULL){
                        queryCtr++;
                        printList(headOut);
                        break;
                    }
                    char printDataV[DATA_MAX_SIZE];
                    int printDataCtr = 0;
                    for(int i = 0; i < strlen(textTemp); i += 2){
                        if(isalpha(textTemp[i]) == 1){
                            printDataV[printDataCtr] = textTemp[i];
                            printDataCtr++;
                        }
                    }
                    printFilter(headOut, printDataV, printDataCtr);
                    queryCtr++;
                    break;
                }
                sscanf(textTemp, " %c %c %d", &charData, &operatorV, &intData);
                compFilter(charData, operatorV, intData);
            } while (strstr(textTemp, ";") == NULL);
            queryBool = false;
        }
        else if (strcmp(operationData, "SORT") == 0){ //SORT
            printf("%s", textTemp);
            fgets(textTemp, DATA_MAX_LENGTH, fp);
            sscanf(textTemp, " %c %c %d", &charData, &operatorV, &intData);
            sortList(charData, intData);
            printf("//Query%d\n", queryCtr);
            printList(headOut);
            queryCtr++;
            queryBool = false;
        }
        else{
            if(queryBool == false){
                printf("//Query%d\n", queryCtr);
                printf("ERROR - No such operation\n\n");
                queryCtr++;
                queryBool = true;
            }
        }
    }
    fclose(fp);

    exit(1);
}
