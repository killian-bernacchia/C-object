#include <stdio.h>
#include <stdlib.h>

typedef int (*func)(void);

typedef struct class{
    func func;
} class;

class* creator(){
    static int i = 0;
    i++;

    class* cl = malloc(sizeof(class));

    func dup_func(int i_){

        void f(){
            int i_f = i; 
            return i_f;
        }

        func f_;
        if(i_>0){
            f_ = dup_func(--i_);
            return f_;
        }
        else return f;
    }

    cl->func = dup_func(i);

    return cl;
}

int main(){

    class* cl = creator();
    class* cl1 = creator();
    class* cl2 = creator();
    class* cl3 = creator();
    class* cl4 = creator();

    
    printf("%i\n",cl->func());
    printf("%i\n",cl2->func());
    printf("%i\n",cl4->func());
    printf("%i\n",cl->func());

}