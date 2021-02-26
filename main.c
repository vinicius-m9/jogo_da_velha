#include <stdio.h>
#include <stdlib.h>

char arr[3][3];

void arrayInit(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(i==2){
                arr[i][j] = ' ';
                return;
            }
            arr[i][j] = '_';
        }
    }
}

void printArray(){
    int ASCII = 65;

    printf("  1 2 3\n");

    for(int i=0; i<3; i++){
        printf("%c ", ASCII++);

        for(int j=0; j<3; j++){
            printf("%c", arr[i][j]);

            if(j!=2)
                printf("|");
        }
        printf("\n");
    }
    printf("\n");
}

int main(void){
    arrayInit();

    printArray();

    return 0;
}
