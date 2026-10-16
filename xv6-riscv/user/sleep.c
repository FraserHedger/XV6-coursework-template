#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc < 2)
    {
        fprintf(2, "This is not valid \n");
        exit(1);

    }
    int sleepnum = atoi(argv[1]);
    pause(sleepnum);

    exit(0);
}