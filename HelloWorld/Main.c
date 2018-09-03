#include <stdio.h>
#include <stdlib.h>

/**
* to actually change variable given at call, prefix *
*/
void square(int *c){
    *c = (*c)*(*c);
}

void changeArrValue(char *t)
{
    *(t+1) = 10;
}

int main(int argc, char *argv[]){

    int a = 5;
    char b = 58;

    // pointer to NULL for the moment
    int *p_a;

    // memory allocation. Returns pointer to first memory slot
    p_a = malloc(sizeof(int) * 1);

    // change the value at this memory slot
    *p_a = 1024;

    /**
    * give MEM ADDRESS with & of var you want to change
    * No need to prefix if given variable is pointer
    */
    square(&a);

    // arrays are pointers :
    char arr[10];
    arr[0] = 5;
    arr[1] = 3;

    // these lines are equivalents :
    printf("\n Value of index 0 is %d", arr[0]);
    printf("\n Value of index 0 is %d", *arr);
    printf("\n Value of index 1 is %d", arr[1]);
    printf("\n Value of index 1 is %d", *(arr+1));

    // manually reserve an array in memory :
    char *myarr; // no mem slot yet, NULL
    myarr = malloc(sizeof(char) * 10);
    myarr[0] = 4;

    printf("\n Value of index 0 myarr is %d", myarr[0]);

    // directly change index 1 value
    changeArrValue(myarr);

    printf("\n Value of index 1 is %d", myarr[1]);


    printf("\n a is now of value %d", a);

    //p_a = &a;

    // a == 15
    // p_a == ??

    printf("\n a = %d", a);
    printf("\n p_a = %d", p_a);
    printf("\n p_a = %d", *p_a);

    // we see *p_a with * for declaration. Then, simply p_a will show memory adress, and *p_a will show actual pointed value

    return 0;
}
