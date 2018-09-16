/*************************************************\
 * Seat assignment logic.
 * Author: Daniel Amador Salas.
 * Created: 26-08-2018.
 * Version: 1.0.
\*************************************************/

//Libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Main.h"

// Global variables
char zoneNames[16] ="DGHSQWRTYUIO"; 
int ind;
int count;
int chairsBought[7]; 

// Template to create a new chair instance.
struct Chair{
    int number;
    int status; // T=true or F=false.
};

// Template to create a new link between two new chairs.
struct linkChair {
    struct Chair chair;
    struct linkChair* link; // Next chair connector.
};

// Template to create a new zone instance.
struct Zone{
    char name;
    struct linkChair* chairs; // Root pointer chair for each zone. 
};

// Template to create a new link between two new zones.
struct linkZone{
    struct Zone zone;
    struct linkZone* link; // Next zone connector.
};
// Template to create a new category.
struct Category{
    char* name;
    int space;
    struct linkZone* zones; // Root pointer for each Category.
};

// Template to crea a new link between two new categories.
struct linkCategory{
    struct Category category;
    struct linkCategory* link; // Next category connector.
} *root; //Root pointer for all categories created for this project.

/************************************************************\
 * Add a new chair linked with the other chairs for each zone
 * Receive: a zone pointer to create their chairs.
 * Return: void.
\************************************************************/
void addNewChair(struct Zone* zone){
    
    for (int i = 0; i <20 ; ++i) {
        struct linkChair* newChair;
        newChair =(struct linkChair*) malloc(sizeof(struct linkChair));
        newChair ->chair.status=0;
        newChair ->chair.number=count;
        count--;
        newChair ->link = NULL;
        if(zone->chairs==NULL)             
            zone->chairs=newChair;
        else{
            newChair->link=zone->chairs;
            zone->chairs=newChair;
        }
    }
};
/**************************************************************\
 * Add a new zone linked with the other zones for each category.
 * Receive: a category pointer to create their zones.
 * Return: void.
\**************************************************************/
void addNewZone(struct Category* category){
    for (int i = 0; i < 4 ; ++i) {
        struct linkZone* newZone=(struct linkZone*) malloc(sizeof(struct linkZone));
        newZone ->zone.name=zoneNames[ind];
        newZone ->zone.chairs=NULL;
        ind+=1;
        newZone -> link=NULL;
        if(category->zones==NULL){
            category->zones=newZone; 
        }
        else{
            newZone->link=category->zones;
            category->zones=newZone;
        }
        addNewChair(&newZone->zone); // Call the method that add new chairs.
    }
};
/*********************************************************************\
 * Add a new category linked with the other categories.
 * Recieve: a char pointer with the root of the name for this category.
 * Return: void.
\*********************************************************************/
void insertCategories(char* name){
    struct linkCategory* newCategory=(struct linkCategory*) malloc(sizeof(struct linkCategory));
    newCategory -> category.name=name;
    newCategory-> category.space=80; // Maximum of available spaces to assign.
    newCategory->category.zones=NULL;
    newCategory->link=NULL;
   if(root==NULL){
       root=newCategory;
   } 
   else{
       newCategory->link=root;
       root=newCategory;
   }
   addNewZone(&newCategory->category); // Call the method that add new zones.
};
/*******************************************************************\
 * Method to verify the information inserted.
 * Receive: nothing.
 * Return: void.
\*******************************************************************/
void printStock(){
    struct linkCategory* ptrCategory= root;
    while(ptrCategory!=NULL){ // Browse categories.
        printf("Category: %s>\n",ptrCategory->category.name);
        struct linkZone* ptrZone=ptrCategory->category.zones;
        while(ptrZone!=NULL){ //Browse zones.
            printf("\t\tZone:%c >\n",ptrZone->zone.name);
            struct linkChair* ptrChair=ptrZone->zone.chairs;
            while(ptrChair!=NULL){ //Browse chairs.
                printf("\t\t\tChair: %i ====> %i\n",ptrChair->chair.number,ptrChair->chair.status);
                ptrChair=ptrChair->link;
            }
            ptrZone=ptrZone->link;
        }
        ptrCategory=ptrCategory->link;
    }
};
/**************************************************************\
 * Search in zones until find available chairs to make 
 the purchase of the requested tickets.
 * Receive: quantity of chairs requested and the category where
 will make the purchase.
 * Return: void.
\**************************************************************/
void buyChairs(int chairRequest, struct Category* category){
    struct linkZone* ptrZones=category->zones;
    int i=0,asigned=0;
    while(ptrZones!=NULL){
        struct linkChair* ptrChairs =ptrZones->zone.chairs;
        while(ptrChairs!=NULL){
            if (ptrChairs->chair.status == 0) {
                ptrChairs->chair.status = 1;
                chairsBought[i]=ptrChairs->chair.number;
                i++; asigned++;
                category->space-=1;
                if (asigned == chairRequest)
                    return;
            }
            ptrChairs = ptrChairs->link;
        }
        ptrZones= ptrZones->link;
    }
};
/*******************************************************\
 * Search a category selected and after that call the 
   method that make the purchase.
 * Receive: quantity of chairs and the category selected name.
\*******************************************************/
void searchCategory(int chairs, const char* name){
    struct linkCategory* ptrCategory=root;
    while(ptrCategory!=NULL){
        if(strcmp(name,ptrCategory->category.name)==0){
            if(ptrCategory->category.space>=chairs) 
                buyChairs(chairs, &ptrCategory->category);
            break;
        }
        ptrCategory=ptrCategory->link;
    }
};
/******************************************************************\
 * For test purposes, the records are filled with test data.
 * Recieve: number of chairs that will recerve for each category.
 * Return: void.
\******************************************************************/
void getTicketsDefault(int chairs){
    
    struct linkCategory* ptrCategory=root;
    while(ptrCategory!=NULL){
        int count=0;
        struct linkZone* ptrZone= ptrCategory->category.zones;
        while(ptrZone!=NULL){
            struct linkChair* ptrChair=ptrZone->zone.chairs;
            while (ptrChair!=NULL){
                if(count<chairs){
                    ptrChair->chair.status=1;
                    ptrCategory->category.space--;
                    count++;
                    
                }else
                    break;
                ptrChair=ptrChair->link;
            }
            ptrZone=ptrZone->link;
        }
       
        ptrCategory=ptrCategory->link;
    }
};
/**************************************************************************\
 * Java connection class . This class is called first of all other classes.
 * Receive: a pointer that save the events, J integer that save the quantity 
of chairs request, a string that save the name  of the proyect and a number
of chairs avaible will be checked.
\**************************************************************************/
jintArray JNICALL Java_controller_Main_nativeGreeting
  (JNIEnv * env, jobject object, jint param1,jstring text,jint reser) {
    // Conver string in char pointer.
    
    const char *org = (*env)->GetStringUTFChars(env,text,NULL);
    // Conver a C array in a JAVA array.
    jintArray array  = (*env)->NewIntArray(env,param1);
    // Reset values.
    root=NULL;
    ind=0;
    count=239;
    
    // Call the method that add new categories.
    insertCategories("Shambhala");
    insertCategories("Avalon");
    insertCategories("Camelot");
    //Buy the default tickests.
    getTicketsDefault(reser);
    // Search the tickets.
    searchCategory(param1,org);
    printStock();
    // Fill the array JNI with  the information fron C array.
    (*env)->SetIntArrayRegion(env,array,0,param1,chairsBought);
    // Return the chairs bou
    return array;
};