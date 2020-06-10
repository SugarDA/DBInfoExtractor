#include <stdio.h>
#include <stdlib.h>
#define maxChar 101


//Structs
typedef struct{
    int year;
    int day;
    int minutes;
    int listlen;
} counterArray;


typedef struct{

    int year;
    int day;
    int minutes;
    double value;
    int listlen;

} txtread;


typedef struct infoLL{

    int year;
    int day;
    int minutes;
    double value;

    struct infoLL *next;

}infoLL;


//Function initialization


txtread* fileread(char filename[maxChar]);
counterArray* counterTxtRead(char filename[maxChar]);
void counterRead(counterArray*arr);
void addBack(infoLL* head,infoLL* node);
infoLL* creatNode(int year, int days, int minutes, double value);
void readLL(infoLL* arr);
infoLL* creatLL(txtread*arr);
infoLL* simpleswapLL (infoLL* head, int pos);
infoLL* sortThatLL(infoLL* head,txtread* arr);
void readLLUnsorted(txtread* arr);


//main
//========================================================================================================================================================================================================
int main()
{
    //***TEST***
    //Erstellt Array "DB" mit .txt inhalt
    //Die func. readLLUnsorted gibt die list aus wie sie im .txt aus,
    txtread* DB= fileread("DB.txt");
    readLLUnsorted(DB);
    //***TEST***


    //***TEST***
    //readLL gibt eine Lineare Liste aus"LL" aus
    //creatLL nimmt einen array vom typ txtread als Eingabe. Und gibt eine LL vom typ infoLL zurück
    infoLL*lis=creatLL(DB);
    //readLL(lis);
    //***TEST***


    //***TEST***
    // für mich zum Testen von simpleswapLL. Ist nicht relevant für dich
    //lis= simpleswapLL(lis,1);
    //readLL(lis);
    //***TEST***


    //***TEST***
    //readLL gibt liste aus. sortThatLL sortiert die liste
    readLL(sortThatLL(lis,DB));
    //***TEST***


    //***TEST***
    //cArr ist ein Array vom typ counter Array. counterTxtRead liest die .txt ein und gibt ein array vom typ counterArray zurück. counterRead gibt den .txt inhalt wieder
    counterArray* cArr = counterTxtRead("DB2.txt");
    counterRead(cArr);
    //***TEST***


    return 0;
}
//========================================================================================================================================================================================================


//Function declaration


txtread* fileread(char filename[maxChar])
{
    int i=0;
    int numyear;
    int numday;
    int nummin;
    double value;


    txtread* databankList = calloc(0,sizeof(txtread));
    FILE* f = fopen(filename,"r");


    if(f==NULL)
    {
        printf("Fehler beim öffnen von %s",filename);
        return NULL;
    }


    while (EOF!=fscanf(f,"%d, %d, %d, %lf",&numyear,&numday,&nummin,&value))
    {
        databankList = (txtread*)realloc(databankList,(i+1)*sizeof(txtread));
        databankList[i].year = numyear;
        databankList[i].day = numday;
        databankList[i].minutes= nummin;
        databankList[i].value = value;
        i++;
    }


    fclose(f);
    databankList[0].listlen = i;
    return databankList;
}


counterArray* counterTxtRead(char filename[maxChar])
{
    int i=0;
    int numbuff[3];


    counterArray* databankList = calloc(0,sizeof(counterArray));
    FILE* f = fopen(filename,"r");


    if(f==NULL)
    {
        printf("Fehler beim öffnen von %s",filename);
        return NULL;
    }


    while (EOF!=fscanf(f,"%d, %d, %d",&numbuff[0],&numbuff[1],&numbuff[2]))
    {
        databankList = (counterArray*)realloc(databankList,(i+1)*sizeof(counterArray));
        databankList[i].year = numbuff[0];
        databankList[i].day = numbuff[1];
        databankList[i].minutes = numbuff[2];
        i++;
    }


    fclose(f);
    databankList[0].listlen = i;
    return databankList;
}


void counterRead(counterArray*arr)
{
    int count=0;
    printf("\n====================================================================================================\n\n");
    for(int i=0;i<arr[0].listlen;i++)
    {
        printf("Nr.:%4d Year: %4d Days: %4d Minutes: %4d\n",i,arr[i].year,arr[i].day,arr[i].minutes);
        count=i;
    }
    printf("\n====================================================================================================\n");

    printf("Count: %4d\n",count+1);
}


void addBack(infoLL* head, infoLL* node)
{
    infoLL* p;
    for(p=head;p->next!=NULL;p=p->next);

    p->next=node;
}


infoLL* creatNode(int year, int days, int minutes, double value)
{
    infoLL* newNode = (infoLL*)malloc(sizeof(infoLL));
    newNode->year=year;
    newNode->day=days;
    newNode->minutes=minutes;
    newNode->value=value;
    newNode->next=NULL;
    return newNode;
}


// liest eine lineare Liste aus. mit min max und mittelwerten
void readLL(infoLL* list)
{
    int i=0;
    printf("\n====================================================================================================\n\n");
    for(infoLL*p=list;p!=NULL;p=p->next)
    {
        printf("Nr.:%4d Year: %4d Days: %4d Minutes: %4d Value: %.3f\n",i,p->year,p->day,p->minutes,p->value);
        i++;
    }
    printf("\n====================================================================================================\n");

    int counter=0;
    txtread* templist= calloc(0,sizeof(txtread));

    for(infoLL*p=list;p!=NULL;p=p->next)
    {
        templist =(txtread*)realloc(templist,(counter+1)*sizeof(txtread));
        templist[counter].year=p->year;
        templist[counter].day=p->day;
        templist[counter].minutes=p->minutes;
        templist[counter].value=p->value;
        counter++;

    }
    printf("Items in DB:    %d",counter);
    double amw=0;
    for(int i=0;i<counter;i++)
    {
        amw=amw + templist[i].value;
    }
    amw=amw/counter;

    printf("\n");
    printf("min:            %.3f\n",templist[0].value);
    printf("max:            %.3f\n",templist[counter-1].value);
    printf("Median:         %.3f\n",templist[counter/2].value);
    printf("Mittelwert:     %.3f\n",amw);
    free(templist);

}


infoLL* creatLL(txtread*arr)
{
    infoLL* head = (infoLL*)malloc(sizeof(infoLL));
    head=creatNode(arr[0].year,arr[0].day,arr[0].minutes,arr[0].value);


    for(int i=1;i<arr[0].listlen;i++)
    {
        addBack(head,creatNode(arr[i].year,arr[i].day,arr[i].minutes,arr[i].value));
    }
    return head;
}


infoLL* simpleswapLL(infoLL* head, int pos)
{
    //Diese swap func deckt bei weitem nicht alle fälle ab.
    //Sie ist nur gemacht für die Sortierfunc. Einige Abfragen müssen in der Sortierfunc. gemacht werden.
    infoLL* preNode;
    infoLL* postNode;
    infoLL* p = head;
    infoLL* node1;
    infoLL* node2;

    if(pos==0)
    {
        node1=p;
        p=p->next;
        node2=p;
        p=p->next;
        postNode=p;

        node2->next=node1;
        node1->next=postNode;
        head=node2;
        return head;
    }

    else
    {
        //functioniert nur wenn pos nicht head ist
        for(int i=0;i<pos-1;i++)
        {
            p=p->next;
        }

        preNode=p;
        p=p->next;

        node1=p;
        p=p->next;

        node2=p;
        p=p->next;

        postNode=p;

        preNode->next=node2;
        node2->next=node1;
        node1->next=postNode;
        return head;

    }
}


infoLL* sortThatLL(infoLL* head, txtread* arr)
{
    infoLL* p;
    infoLL* cNode1;
    infoLL* cNode2;


    for (int i=0;i<arr[0].listlen-1;i++)
    {
        for(int j=0;j<arr[0].listlen-i-1;j++)
        {
            p=head;
            for(int k=0;k<j;k++)
            {
                p=p->next;
            }

            cNode1=p;
            p=p->next;
            cNode2=p;
            if(cNode1->value>cNode2->value)
            {
                head = simpleswapLL(head,j);
            }
        }
    }
    return head;
}


void readLLUnsorted(txtread* arr)
{
    printf("\n====================================================================================================\n\n");
    for(int i=0;i<arr[0].listlen;i++)
    {
        printf("Nr.:%4d Year: %4d Days: %4d Minutes: %4d Value: %.3f\n",i,arr[i].year,arr[i].day,arr[i].minutes,arr[i].value);
    }
    printf("\n====================================================================================================\n");
}
