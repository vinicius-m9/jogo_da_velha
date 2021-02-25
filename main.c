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


int main(void){
    arrayInit();

    return 0;
}
