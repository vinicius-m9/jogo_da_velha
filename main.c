#include <stdio.h>
#include <stdlib.h>

// biblioteca para utilizar a funcao toupper()
#include <ctype.h>

// biblioteca para utilizar dados booleanos
#include <stdbool.h>

char arr[3][3];

void arrayInit(void){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(i==2)
                arr[i][j] = ' ';
            else
                arr[i][j] = '_';
        }
    }
}

int charToInt (char line){
    switch(toupper(line)){
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
    }
    return -1;
}

int validChar (char symbol){
    if(symbol == 'X' || symbol == 'O')
        return 1;

    return 0;
}

int validCoord(char line, int column){
    int i = charToInt(line), j = column-1;

    if(i>=0 && i<3 && j>=0 && j<3)
        return 1;

    return 0;
}

int coordEmpty(char line, int column){
    int i = charToInt(line), j = column-1;

    if(!validChar(arr[i][j]))
        return 1;

    return 0;
}

int lineWin(void){
    int count = 0;

    for(int i=0; i<3; i++){
        for(int j=0; j<2; j++){
            if(validChar(arr[i][j]) && arr[i][j] == arr[i][j+1])
                count++;
        }
        if(count == 2)
            return 1;

        count = 0;
    }
    return 0;
}

int columnWin(void){
    int count = 0;

    for(int j=0; j<3; j++){
        for(int i=0; i<2; i++){
            if(validChar(arr[i][j]) && arr[i][j] == arr[i+1][j])
                count++;
        }
        if(count == 2)
            return 1;

        count = 0;
    }
    return 0;
}

int diagonalWin(void){
    int count = 0;

    // main diagonal
    for(int i=0; i<2; i++){
        if(validChar(arr[i][i]) && arr[i][i] == arr[i+1][i+1])
            count++;
    }
    if(count == 2)
        return 1;

    count = 0;

    // secondary diagonal
    for(int i=0; i<2; i++){
        if(validChar(arr[i][i]) && arr[i][2-i] == arr[i+1][1-i])
            count++;
    }
    if(count == 2)
        return 1;

    return 0;
}

int winner(void){
    if(lineWin() || columnWin() || diagonalWin())
        return 1;

    return 0;
}

void printArray(void){
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

int menuOption(void){
    int option;

    printf("JOGO DA VELHA\n");
    printArray();
    printf("Escolha o modo de jogo:\n 1. jogador X jogador\n 2. jogador X maquina\n");

    scanf("%i", &option);

    /* OS variation
    * system("cls"); -> Windows
    * system("clear"); -> Linux
    */
    system("cls");

    return option;
}

int main(void){
    arrayInit();

    menuOption();

    return 0;
}
