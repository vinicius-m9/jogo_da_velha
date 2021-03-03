#include <stdio.h>
#include <stdlib.h>

/**
* biblioteca para utilizar a funcao toupper()
*/
#include <ctype.h>

/**
* biblioteca para utilizar dados booleanos
*/
#include <stdbool.h>

/**
* biblioteca para utilizar a funcao time()
*/
#include <time.h>

char arr[3][3];
char player1[51], player2[51];
char symbol1, symbol2;

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

int validSymbol(char symbol){
    symbol = toupper(symbol);

    if(symbol == 'X' || symbol == 'O')
        return 1;

    return 0;
}

int validCoord(int line, int column){
    if(line>=0 && line<3 && column>=0 && column<3)
        return 1;

    return 0;
}

int coordEmpty(int line, int column){
    if(!validSymbol(arr[line][column]))
        return 1;

    return 0;
}

int lineWin(void){
    int count = 0;

    for(int i=0; i<3; i++){
        for(int j=0; j<2; j++){
            if(validSymbol(arr[i][j]) && arr[i][j] == arr[i][j+1])
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
            if(validSymbol(arr[i][j]) && arr[i][j] == arr[i+1][j])
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

    /**
    * main diagonal
    */
    for(int i=0; i<2; i++){
        if(validSymbol(arr[i][i]) && arr[i][i] == arr[i+1][i+1])
            count++;
    }
    if(count == 2)
        return 1;

    count = 0;

    /**
    * secondary diagonal
    */
    for(int i=0; i<2; i++){
        if(validSymbol(arr[i][i]) && arr[i][2-i] == arr[i+1][1-i])
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

void playerMove(char player[51], char symbol){
    int j, line, column;
    char i;

    printf("Vez de %s. Indique linha e coluna para jogar\n", player);

    printf("linha:\n");
    scanf(" %c", &i);
    line = toupper(i) - 65;

    printf("coluna:\n");
    scanf("%i", &j);
    column = j - 1;

    while(!validCoord(line, column) || !coordEmpty(line, column)){
        printf("Coordenada invalida. Digite novamente!\n");

        printf("linha:\n");
        scanf(" %c", &i);
        line = toupper(i) - 65;

        printf("coluna:\n");
        scanf("%i", &j);
        column = j - 1;
    }

    arr[line][column] = toupper(symbol);

    /**
    * OS variation
    * system("cls"); -> Windows
    * system("clear"); -> Linux
    */
    system("cls");
}

void botMove(char symbol){
    int line = rand() % 3, column = rand() % 3;

    while(!validCoord(line, column) || !coordEmpty(line, column)){
        line = rand() % 3;
        column = rand() % 3;
    }

    arr[line][column] = toupper(symbol);

    /**
    * OS variation
    * system("cls"); -> Windows
    * system("clear"); -> Linux
    */
    system("cls");
}

void playerXplayer(void){
    int turn = 0;

    while(!winner() && turn < 9){
        printArray();

        if(turn % 2 == 0)
            playerMove(player1, symbol1);
        else
            playerMove(player2, symbol2);

        turn++;
    }

    printArray();

    /**
    * correcao para identificar o ganhador
    */
    turn -= 1;

    if(winner() && turn % 2 == 0){
        printf("%s venceu!", player1);
        return;
    }
    if(winner() && turn % 2 != 0){
        printf("%s venceu!", player2);
        return;
    }
    printf("Deu velha!");
}

void playerXbot(void){
    int turn = rand() % 2, stop = turn + 9;

    while(!winner() && turn < stop){
        printArray();

        if(turn % 2 == 0)
            playerMove(player1, symbol1);
        else
            botMove(symbol2);

        turn++;
    }

    printArray();

    /**
    * correcao para identificar o ganhador
    */
    turn -= 1;

    if(winner() && turn % 2 == 0){
        printf("%s venceu!", player1);
        return;
    }
    if(winner() && turn % 2 != 0){
        printf("Maquina venceu!");
        return;
    }
    printf("Deu velha!");
}

void menuOption(void){
    int option;

    printf("JOGO DA VELHA\n");
    printArray();
    printf("Escolha o modo de jogo:\n 1. jogador X jogador\n 2. jogador X maquina\n");

    scanf("%i", &option);

    /**
    * OS variation
    * system("cls"); -> Windows
    * system("clear"); -> Linux
    */
    system("cls");

    if(option == 1){
        printf("Digite o nome do jogador 1 (ex.: nome_sobrenome):\n");
        scanf("%s", player1);

        printf("\nDigite o simbolo que deseja utilizar: X ou O\n");
        scanf(" %c", &symbol1);
        printf("\n");

        while(!validSymbol(symbol1)){
            printf("simbolo invalido! Digite novamente:\n");
            scanf(" %c", &symbol1);
            printf("\n");
        }

        printf("Digite o nome do jogador 2 (ex.: nome_sobrenome):\n");
        scanf("%s", player2);

        if(toupper(symbol1) == 'X')
            symbol2 = 'O';
        else
            symbol2 = 'X';

        /**
        * OS variation
        * system("cls"); -> Windows
        * system("clear"); -> Linux
        */
        system("cls");

        playerXplayer();
    }else{
        printf("Digite o nome do jogador (ex.: nome_sobrenome):\n");
        scanf("%s", player1);

        printf("\nDigite o simbolo que deseja utilizar: X ou O\n");
        scanf(" %c", &symbol1);
        printf("\n");

        while(!validSymbol(symbol1)){
            printf("simbolo invalido! Digite novamente:\n");
            scanf(" %c", &symbol1);
            printf("\n");
        }

        if(toupper(symbol1) == 'X')
            symbol2 = 'O';
        else
            symbol2 = 'X';

        /**
        * OS variation
        * system("cls"); -> Windows
        * system("clear"); -> Linux
        */
        system("cls");

        playerXbot();
    }
}

int main(void){
    /**
    * modifica a seed para gerar numeros aleatorios toda vez que o
    * programa for executado
    */
    srand(time(NULL));

    arrayInit();

    menuOption();

    return 0;
}
