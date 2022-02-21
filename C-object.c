#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ERROR_CODE;//code erreur (pour la lisibilité)

/*******************************************
*
*  DEFINITION DE LA STRUCUTRE DE LA CLASSE
*
********************************************/

typedef struct mc MyClass; //ma classe avec les accès publiques
typedef struct pc ClassPrivate; //la partie privé de ma classe

typedef struct pc
{
    int privateVar1; // une variable privé
    int privateVar2; // une variable privé
} ClassPrivate;

typedef struct mc
{
    const MyClass* (*createMyClass)(int,int,int,int);//initialisateur

    const ERROR_CODE (*toString)(MyClass*, char*);//toString, tu connais
    
    const ERROR_CODE (*setPrivateVar1)(MyClass*, int);// un setter, -1 si fail sinon 0
    const ERROR_CODE (*setPrivateVar2)(MyClass*, int);// un setter, -1 si fail sinon 0
    
    const int (*getPrivateVar1)(MyClass*);// un getter d'une var private
    const int (*getPrivateVar2)(MyClass*);// un getter d'une var private
    
    const int occ; // occurence (qui sera simplement l'index dans le tableau des ClassPrivate)
    int publicVar1;// une variable public
    int publicVar2;// une variable public
    const ClassPrivate* privateInitiliser;
} MyClass;

/*******************************************
*
*  DEFINITION DES FONCTIONS DE LA CLASSE
*
********************************************/

MyClass* createMyClass(int var1, int var2, int priv_var1, int priv_var2);

ERROR_CODE toString(MyClass* myClass, char* buffer);

ERROR_CODE setPrivateVar1(MyClass* myClass, int i);
ERROR_CODE setPrivateVar2(MyClass* myClass, int i);

int getPrivateVar1(MyClass* myClass);
int getPrivateVar2(MyClass* myClass);

ClassPrivate* getClassPrivate(MyClass* myClass);

/*******************************************
*
*          CODE DES FONCTIONS
*
********************************************/

MyClass* createMyClass(int var1, int var2, int priv_var1, int priv_var2)
{

    //initialisation global
    static int lastOcc = 0;
    static ClassPrivate* privateTab[50];
    if(lastOcc==0){
        MyClass privateInitiliser = {.privateInitiliser=privateTab};
        getClassPrivate(&privateInitiliser);
    }

    //initialisation privé
    privateTab[lastOcc] = malloc(sizeof(ClassPrivate));
    *privateTab[lastOcc] = (ClassPrivate) {.privateVar1=priv_var1, .privateVar2=priv_var2};
    //initialisation public
    MyClass localClasse =
    {
        .publicVar1=var1,
        .publicVar2=var2,
        .occ=lastOcc,

        .createMyClass= &createMyClass,//initialisateur
        .toString=&toString,
        .setPrivateVar1=&setPrivateVar1,// un setter, -1 si fail sinon 0
        .setPrivateVar2=&setPrivateVar2,// un setter, -1 si fail sinon 0
        .getPrivateVar1=&getPrivateVar1,// un getter d'une var private
        .getPrivateVar2=&getPrivateVar2,// un getter d'une var private
        .privateInitiliser=NULL
    };
    lastOcc++;
    
    MyClass* p_myClass = malloc(sizeof(MyClass));

    bcopy(&localClasse,p_myClass,sizeof(MyClass));
    return p_myClass;
}

ERROR_CODE toString(MyClass* myClass, char* buffer)
{
    strcpy(buffer,"toString TODO");
    return 0;
}


ClassPrivate* getClassPrivate(MyClass* myClass)
{
    static int initialised = 0;
    static ClassPrivate** privateTab;
    if(initialised==0)
    {
        privateTab = myClass->privateInitiliser;
        initialised = 1;
        return NULL;
    }

    return privateTab[myClass->occ];
}

int getPrivateVar1(MyClass* myClass)
{
    return (getClassPrivate(myClass))->privateVar1;
}

int getPrivateVar2(MyClass* myClass)
{
    return (getClassPrivate(myClass))->privateVar2;
}

ERROR_CODE setPrivateVar1(MyClass* myClass, int i)
{
    (getClassPrivate(myClass))->privateVar1=i;
    return 0;
}

ERROR_CODE setPrivateVar2(MyClass* myClass, int i)
{
    (getClassPrivate(myClass))->privateVar2=i;
    return 0;
}





int main()
{
    MyClass* myClass = createMyClass(10,2,-1,-20);
    // publicVar1 = 10, publicVar2 = 2
    // privateVar1 = -1, privateVar2 = -20

    //le toString est à faire (les strings c'est pas mon truc)
    char buffer[20];
    myClass->toString(myClass,buffer);
    printf("%s\n",buffer); // "toString TODO"


    //modification de valeurs
    myClass->publicVar2 = 20; 
    myClass->setPrivateVar1(myClass, -10);
    // publicVar1 = 10, publicVar2 = 20, 
    // privateVar1 = -10, privateVar2 = -20

    printf("%i\n", myClass->publicVar1);//10
    printf("%i\n", myClass->publicVar2);//20
    printf("%i\n", myClass->getPrivateVar1(myClass));//-10
    printf("%i\n", myClass->getPrivateVar2(myClass));//-20       

    MyClass* myClass2 = createMyClass(100,20,-10,-200);
    // publicVar1 = 100, publicVar2 = 20
    // privateVar1 = -10, privateVar2 = -200

    //le toString est à faire (les strings c'est pas mon truc)
    myClass2->toString(myClass2,buffer);
    printf("%s\n",buffer); // "toString TODO"


    //modification de valeurs
    myClass2->publicVar2 = 200; 
    myClass2->setPrivateVar1(myClass2, -100);
    // publicVar1 = 100, publicVar2 = 200, 
    // privateVar1 = -100, privateVar2 = -200

    printf("%i\n", myClass2->publicVar1);//100
    printf("%i\n", myClass2->publicVar2);//200
    printf("%i\n", myClass2->getPrivateVar1(myClass2));//-100
    printf("%i\n", myClass2->getPrivateVar2(myClass2));//-200
}
