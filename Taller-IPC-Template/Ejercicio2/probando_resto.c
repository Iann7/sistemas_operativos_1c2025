#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"
int main(){
    int a=-1;
    int b=3;
    int c=a%b;
    printf("%d \n",c);
    return 0;
}