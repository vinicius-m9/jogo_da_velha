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

/**
* declaracao de variaveis globais
*/
char arr[3][3];
char player1[51], player2[51];
char symbol1, symbol2;

/**
* declaracao de funcoes
*/
void arrayInit(void);
void menuOption(void);
void printArray(void);
int validSymbol(char symbol);
void playerXplayer(void);
void playerXbot(void);
void botMove(int turn);
int botWin(void);
int botBlock(void);
int botLineWin(void);
int botColumnWin(void);
int botDiagonalWin(void);
int botLineBlock(void);
int botColumnBlock(void);
int botDiagonalBlock(void);
void playerMove(char player[51], char symbol);
int validCoord(int line, int column);
int coordEmpty(int line, int column);
int winner(void);
int lineWin(void);
int columnWin(void);
int diagonalWin(void);

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

int validSymbol(char symbol){
    symbol = toupper(symbol);

    if(symbol == 'X' || symbol == 'O')
        return 1;

    return 0;
}

void playerXplayer(void){
    int turn, stop;

    if(toupper(symbol1) == 'X')
        turn = 0;
    else
        turn = 1;

    stop = turn + 9;

    while(!winner() && turn < stop){
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
    int turn, stop;

    if(toupper(symbol1) == 'X')
        turn = 0;
    else
        turn = 1;

    stop = turn + 9;

    while(!winner() && turn < stop){
        printArray();

        if(turn % 2 == 0)
            playerMove(player1, symbol1);
        else
            botMove(turn);

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

void botMove(int turn){
    int line = rand() % 3, column = rand() % 3;

    if(turn == 1){
        if(arr[1][1] == toupper(symbol1)){
            int arrAux[2] = {0, 2};
            int i = arrAux[rand() % 2], j = arrAux[rand() % 2];

            arr[i][j] = toupper(symbol2);

            /**
            * OS variation
            * system("cls"); -> Windows
            * system("clear"); -> Linux
            */
            system("cls");

            return;
        }
        else{
            arr[1][1] = toupper(symbol2);

            /**
            * OS variation
            * system("cls"); -> Windows
            * system("clear"); -> Linux
            */
            system("cls");

            return;
        }
    }

    if(botWin())
        return;

    if(botBlock())
        return;

    while(!validCoord(line, column) || !coordEmpty(line, column)){
        line = rand() % 3;
        column = rand() % 3;
    }

    arr[line][column] = toupper(symbol2);

    /**
    * OS variation
    * system("cls"); -> Windows
    * system("clear"); -> Linux
    */
    system("cls");
}

int botWin(void){
    if(botLineWin() || botColumnWin() || botDiagonalWin())
        return 1;

    return 0;
}

int botBlock(void){
    if(botLineBlock() || botColumnBlock() || botDiagonalBlock())
        return 1;

    return 0;
}

int botLineWin(void){
    int win = 0, line, column;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(arr[i][j] == toupper(symbol2))
                win++;
            else{
                line = i;
                column = j;
            }
        }

        if(win == 2 && coordEmpty(line, column)){
            arr[line][column] = toupper(symbol2);

            /**
            * OS variation
            * system("cls"); -> Windows
            * system("clear"); -> Linux
            */
            system("cls");

            return 1;
        }

        win = 0;
    }

    return 0;
}

int botColumnWin(void){
    int win = 0, line, column;

    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 3; i++){
            if(arr[i][j] == toupper(symbol2))
                win++;
            else{
                line = i;
                column = j;
            }
        }

        if(win == 2 && coordEmpty(line, column)){
            arr[line][column] = toupper(symbol2);

            /**
            * OS variation
            * system("cls"); -> Windows
            * system("clear"); -> Linux
            */
            system("cls");

            return 1;
        }

        win = 0;
    }

    return 0;
}

int botDiagonalWin(void){
    int win = 0, line, column;

    /**
    * main diagonal
    */
    for(int i = 0; i < 3; i++){
        if(arr[i][i] == toupper(symbol2))
            win++;
        else{
            line = i;
            column = i;
        }
    }

    if(win == 2 && coordEmpty(line, column)){
        arr[line][column] = toupper(symbol2);

        /**
        * OS variation
        * system("cls"); -> Windows
        * system("clear"); -> Linux
        */
        system("cls");

        return 1;
    }

    win = 0;

    /**
    * secondary diagonal
    */
    for(int i = 0; i < 3; i++){
        if(arr[i][2 - i] == toupper(symbol2))
            win++;
        else{
            line = i;
            column = 2 - i;
        }
    }

    if(win == 2 && coordEmpty(line, column)){
        arr[line][column] = toupper(symbol2);

        /**
        * OS variation
        * system("cls"); -> Windows
        * system("clear"); -> Linux
        */
        system("cls");

        return 1;
    }

    win = 0;

    return 0;
}

int botLineBlock(void){
    int block = 0, line, column;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(arr[i][j] == toupper(symbol1))
                block++;
            else{
                line = i;
                column = j;
            }
        }

        if(block == 2 && coordEmpty(line, column)){
            arr[line][column] = toupper(symbol2);

            /**
            * OS variation
            * system("cls"); -> Windows
            * system("clear"); -> Linux
            */
            system("cls");

            return 1;
        }

        block = 0;
    }

    return 0;
}

int botColumnBlock(void){
    int block = 0, line, column;

    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 3; i++){
            if(arr[i][j] == toupper(symbol1))
                block++;
            else{
                line = i;
                column = j;
            }
        }

        if(block == 2 && coordEmpty(line, column)){
            arr[line][column] = toupper(symbol2);

            /**
            * OS variation
            * system("cls"); -> Windows
            * system("clear"); -> Linux
            */
            system("cls");

            return 1;
        }

        block = 0;
    }

    return 0;
}

int botDiagonalBlock(void){
    int block = 0, line, column;

    for(int i = 0; i < 3; i++){
        if(arr[i][2 - i] == toupper(symbol1))
            block++;
        else{
            line = i;
            column = 2 - i;
        }
    }

    if(block == 2 && coordEmpty(line, column)){
        arr[line][column] = toupper(symbol2);

        /**
        * OS variation
        * system("cls"); -> Windows
        * system("clear"); -> Linux
        */
        system("cls");

        return 1;
    }

    block = 0;

    for(int i = 0; i < 3; i++){
        if(arr[i][i] == toupper(symbol1))
            block++;
        else{
            line = i;
            column = i;
        }
    }

    if(block == 2 && coordEmpty(line, column)){
        arr[line][column] = toupper(symbol2);

        /**
        * OS variation
        * system("cls"); -> Windows
        * system("clear"); -> Linux
        */
        system("cls");

        return 1;
    }

    block = 0;

    return 0;
}

void playerMove(char player[51], char symbol){
    int j, line, column;
    char i;

    printf("Vez de %s. Indique linha e coluna para jogar\n", player);

    scanf(" %c", &i);
    line = toupper(i) - 65;

    scanf("%i", &j);
    column = j - 1;

    while(!validCoord(line, column) || !coordEmpty(line, column)){
        printf("Coordenada invalida. Digite novamente!\n");

        scanf(" %c", &i);
        line = toupper(i) - 65;

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

int validCoord(int line, int column){
    if(line >= 0 && line < 3 && column >= 0 && column < 3)
        return 1;

    return 0;
}

int coordEmpty(int line, int column){
    if(!validSymbol(arr[line][column]))
        return 1;

    return 0;
}

int winner(void){
    if(lineWin() || columnWin() || diagonalWin())
        return 1;

    return 0;
}

int lineWin(void){
    int count = 0;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++)
            if(validSymbol(arr[i][j]) && arr[i][j] == arr[i][j+1])
                count++;

        if(count == 2)
            return 1;

        count = 0;
    }
    return 0;
}

int columnWin(void){
    int count = 0;

    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 2; i++)
            if(validSymbol(arr[i][j]) && arr[i][j] == arr[i+1][j])
                count++;

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
    for(int i = 0; i < 2; i++)
        if(validSymbol(arr[i][i]) && arr[i][i] == arr[i+1][i+1])
            count++;

    if(count == 2)
        return 1;

    count = 0;

    /**
    * secondary diagonal
    */
    for(int i = 0; i < 2; i++)
        if(validSymbol(arr[i][2-i]) && arr[i][2-i] == arr[i+1][1-i])
            count++;

    if(count == 2)
        return 1;

    return 0;
}
