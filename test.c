#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
struct IntsDefined
{
    const int i3;
    const int i2;
    int i;
} IntsDefined ={9};

typedef struct IntsDefined IntsPreDefined;

IntsPreDefined ints ={2,8,6};

void testDefined()
{
    ints.i=1;
    printf("%i | %i | %i | %i |\n",IntsDefined.i3,ints.i3,ints.i2,ints.i);
}

typedef struct constStruct
{
    const int i;
} constStruct;

typedef struct unconstStruct
{
    int i;
} unconstStruct;

void testConst()
{
    printf("const test\n");
    constStruct myConst = {.i=5, };
    printf("myConst.i=%i\n",myConst.i);
    unconstStruct* p_unconst = (unconstStruct*) &myConst;
    p_unconst->i=6;
    printf("myConst.i=%i\n",myConst.i);
}

typedef struct small
{
    int a;
    int b;
}small;

typedef struct big
{
    struct small s;
    int c;
    int d;
}big;

void testBigSmall()
{
    printf("big/small test\n");
    big bigOne;
    bigOne = (big) {1,2,3,4};
    printf("bigOne : %i, %i, %i, %i\n",bigOne.s.a,bigOne.s.b,bigOne.c,bigOne.d);
    small* p_small = (small*) &bigOne;
    p_small->a=4;
    p_small->b=3;
    printf("bigOne : %i, %i, %i, %i\n",bigOne.s.a,bigOne.s.b,bigOne.c,bigOne.d);    
    (p_small+1)->a=2;
    (p_small+1)->b=1;
    printf("bigOne : %i, %i, %i, %i\n",bigOne.s.a,bigOne.s.b,bigOne.c,bigOne.d);  
}

typedef struct MyStruct
{
    int a;
    int b;
    char c[5];
    const int d;
} MyStruct;

MyStruct* testMalloc()
{
    printf("malloc test\n");
    MyStruct patern_var = (MyStruct) {1,2,"345",6};
    MyStruct* p_var = malloc(sizeof(MyStruct));

    bcopy(&patern_var,p_var,sizeof(MyStruct));

    printf("%i%i%s%i\n",p_var->a,p_var->b,p_var->c,p_var->d);
    return p_var;
}


typedef void (*ptr_f)(void);

void aFunction()
{
    printf("function returned and executed\n");
}

ptr_f testReturnFunctionPointer()
{
    return &aFunction;
}


ptr_f ReturnPersonalizedFunction(int i)
{
    void localFunction()
    {
        printf("executed %i\n",i);
    }
    printf("created\n");

    ptr_f p_localF = &localFunction;

    //ptr_f p_out_F = malloc(sizeof(localFunction));
    //bcopy(&localFunction, p_out_F, sizeof(localFunction));
    
    return p_localF;
}

void testReturnPersonalizedFunction()
{
    ptr_f p_f1 = ReturnPersonalizedFunction(1);
    p_f1();
    ptr_f p_f2 = ReturnPersonalizedFunction(2);
    p_f1();
    ReturnPersonalizedFunction(3);
    p_f2();
}

void testVariableForkInitialisationAvant()
{
    int x = 0;
    printf("A has x = %d \t|%li\n", x,(long int) &x);  
    if (fork() == 0)
    {
        --x;
        printf("B has x = %d \t|%li\n", x,(long int) &x);
    }
    else
    {
        ++x;
        printf("C has x = %d \t|%li\n", x,(long int) &x);
    }
    printf("D has x = %d \t|%li\n", x,(long int) &x);
}

void testVariableForkInitialisationApres()
{
    int x = 10;
    printf("A has x = %d \t|%li\n", x,(long int) &x);  
    if (fork() == 0)
    {
        int x = 20;
        printf("B has x = %d \t|%li\n", x,(long int) &x);
    }
    else
    {
        int x = 30;
        printf("C has x = %d \t|%li\n", x,(long int) &x);
    }
    printf("D has x = %d \t|%li\n", x,(long int) &x);
}

void testFonctionForkInitialisationApres()
{
    void f(){};
    void (*pt)(void) = &f;

    printf("A has %li|%li\n",(long int) &f, (long int)pt);  


    if (fork() == 0)
    {
        void f(){
            printf("My function");
        }
        pt=&f;
        printf("B has %li|%li\n",(long int) &f, (long int)pt);  
    }
    f();
    printf("C has %li|%li\n",(long int) &f, (long int)pt);  
}

typedef struct
{
    int id;
    ptr_f function;
}object;

object* createObject()
{
    static int nbOcc = 0;
    int i = 0;
    while(1);
}


int main()
{
    printf("start\n");

    //testDefined();

    //testConst();

    //testBigSmall();

    //MyStruct* p_var = testMalloc();
    //printf("%i%i%s%i\n",p_var->a,p_var->b,p_var->c,p_var->d);

    //testReturnFunctionPointer()();

    //testReturnPersonalizedFunction();

    testVariableForkInitialisationAvant();

    testVariableForkInitialisationApres();

    testFonctionForkInitialisationApres();
    testFonctionForkInitialisationApres();

}
