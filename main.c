#include <stdio.h>
#include <stdlib.h>
#define maxChar 101


//Structs


typedef struct{

    int date;
    int value;
    int listlen;

} txtread;

typedef struct infoLL{

    int date;
    int value;

    struct infoLL *next;

}infoLL;


//Function initialization


txtread* fileread(char filename[maxChar]);
infoLL* addStart(infoLL* head,infoLL* node);
void addBack(infoLL* head,infoLL* node);
infoLL* creatNode(int date, int value);
void readLL(infoLL* arr);
infoLL* creatLL(txtread*arr);


//main
//====================================================================================================
int main()
{
    //***TEST***
    //Erstellt Array "DB" mit .txt inhalt
    txtread* DB= fileread("DB.txt");
    printf("\n==================================================\n");
    for(int i=0;i<DB[0].listlen;i++)
    {
        printf("Nr.: %5d Wert L: %5d Wert R: %5d\n",i,DB[i].date,DB[i].value);
    }
    printf("\n==================================================\n");
    //***TEST***


    //***TEST***
    //readLL gibt eine Lineare Liste aus"LL" aus
    //creatLL nimmt einen array vom typ txtread als Eingabe. Und gibt eine LL vom typ infoLL zurück
    readLL(creatLL(DB));
    //***TEST***
    return 0;
}
//====================================================================================================


//Function declaration


txtread* fileread(char filename[maxChar])
{
    int i=0;
    int numbuff[2];


    txtread* databankList = calloc(0,sizeof(txtread));
    FILE* f = fopen(filename,"r");


    if(f==NULL)
    {
        printf("Fehler beim öffnen von %s",filename);
        return NULL;
    }


    while (EOF!=fscanf(f,"%d %d",&numbuff[0],&numbuff[1]))
    {
        databankList = (txtread*)realloc(databankList,(i+1)*sizeof(txtread));
        databankList[i].date = numbuff[0];
        databankList[i].value = numbuff[1];
        i++;
    }


    fclose(f);
    databankList[0].listlen = i;
    return databankList;
}


infoLL* addStart(infoLL* head,infoLL* node)
{
    node->next = head;
    head = node;
    return head;
}


void addBack(infoLL* head, infoLL* node)
{
    infoLL* p;
    for(p=head;p->next!=NULL;p=p->next);

    p->next=node;
}


infoLL* creatNode(int date, int value)
{
    infoLL* newNode = (infoLL*)malloc(sizeof(infoLL));
    newNode->date=date;
    newNode->value=value;
    newNode->next=NULL;
    return newNode;
}


void readLL(infoLL* list)
{
    int i=0;
    printf("\n==================================================\n");
    for(infoLL*p=list;p!=NULL;p=p->next)
    {
        printf("Nr.: %5d Wert L: %5d Wert R: %5d\n",i,p->date,p->value);
        i++;
    }
    printf("\n==================================================\n");
}


infoLL* creatLL(txtread*arr)
{
    infoLL* head = (infoLL*)malloc(sizeof(infoLL));
    head=creatNode(arr[0].date,arr[0].value);


    for(int i=1;i<arr[0].listlen;i++)
    {
        addBack(head,creatNode(arr[i].date,arr[i].value));
    }
    return head;
}
