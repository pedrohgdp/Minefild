#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    
    int isBomb;
    int isOpen;
    int bombInN;
    
}celOfBoard; //Struc for any cell of board

celOfBoard board[10][10];
int size = 10;
int l, c;


//Function to start the board with all cell values null
void startBoard(){
    for(int line = 0; line < size; line++){
        for(int column = 0; column < size; column++){
            board[line][column].isBomb = 0;
            board[line][column].isOpen = 0;
            board[line][column].bombInN = 0;
        }
    }
}

//Sort bomb for the table
void sortBomb(int nBombs){
    int line;
    int column;
    
    srand(time(NULL)); //At each program start, the generated values change
    for(int i = 0; i < nBombs; i++){
        line = rand() % size;
        column = rand() % size;

        if(board[line][column].isBomb == 0){
            board[line][column].isBomb = 1;
        }else if(board[line][column].isBomb == 1){
            i--; // Return i - 1 and sort a new space for bomb
        }
    }
}

//Function to calculate the number of bombs in neighbors
void quantBombInNei(){
    for(int line = 0; line < size; line++){
        for(int column = 0; column < size; column++){
            board[line][column].bombInN = bombInNeibo(line, column);
            //Here we call bomb in neibo function
        }
    }
}

//This function will see if each neighboring space contains a bomb and add 1 to the variable quantity of bomb
int bombInNeibo(int l, int c){
    int quantBomb = 0;
    if(checksPosition(l-1,c) == 1 && board[l-1][c].isBomb == 1){
        quantBomb++;
    }
    if(checksPosition(l+1,c) == 1 && board[l+1][c].isBomb == 1){
        quantBomb++;
    }
    if(checksPosition(l,c+1) == 1 && board[l][c+1].isBomb == 1){
        quantBomb++;
    }
    if(checksPosition(l,c-1) == 1 && board[l][c-1].isBomb == 1){
        quantBomb++;
    }
    return quantBomb;
}

//Verific if position is valid
int checksPosition(int l, int c){
    if(l >= 0 && l < size && c >= 0 && c < size){
        return 1;
    }else{
        return 0;
    }
}

//Print board
void printBoard(){
    printf("\n\n\t ");
    printf("\n\n\t     0   1   2   3   4   5   6   7   8   9");
    printf("\n\t   -----------------------------------------\n");
    for(l = 0; l < size; l++){
        printf("\t   |");
        for(c = 0; c < size; c++){
            if(board[l][c].isOpen){
                if(board[l][c].isBomb){
                    printf(" * ");
                }else{
                    printf(" %d ", board[l][c].bombInN);    
                }
            }
            else{
                printf("   ");
            }printf("|");
        }
        printf("\n\t   -----------------------------------------\n");
    }
}


void openCell(int l, int c){
    //Checks if position is valid and is not open
    if(checksPosition(l, c) && board[l][c].isOpen == 0){
        //open a position
        board[l][c].isOpen = 1;
        //call the same function for open de neighbors if they don't have a bomb 
        if(board[l][c].bombInN == 0){
            openCell(l-1, c);
            openCell(l+1, c);
            openCell(l, c-1);
            openCell(l, c+1);
        }
    }
}


//This is function play
void play(){
    int line, column;
    
    while(1){
        printBoard();
        do{
            printf("Enter a row and a column: ");
            scanf("%d%d", &line, &column);
        
            if(checksPosition(line, column) == 0 || board[line][column].isOpen == 1){
                printf("\nPosition invalid, try again!\n");
            }
        }while(checksPosition(line, column) == 0 || board[line][column].isOpen == 1);
        
        openCell(line,column);
        
        if(checksVitory() == 1 && board[line][column].isBomb == 0){
            printBoard();
            printf("\n\tYou win!!");
            break;
        }else if(board[line][column].isBomb == 1){
            printBoard();
            printf("\n\tYou lost, the position is a bomb!!");
            break;
        }else{
            continue;
        }
    }
}


int checksVitory(){
    for(l = 0; l < size; l++){
        for(c = 0; c < size; c++){
            if (board[l][c].isOpen == 0 && board[l][c].isBomb == 0) // if position is not open and no have bomb
            {
                return 0; // return 0 (It has a closed position and no have bomb)
            }else{
                return 1; //every position without a bomb is open
            }           
        }
    }
}



//Main function for start game
int main(){    
        startBoard();
        sortBomb(10);
        quantBombInNei();
        printf("\n\t\tMINEFIELD\n");
        play();
    return 0;
}
