#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct field {
	char state;
}field;

field board[6][7];
char name1[20];
char name2[20];
int option, win, count;
char turn = 'X';
void mainMenu();
void instruction();
void pNames();
void clearBoard(field board[6][7]);
void printBoard(field board[6][7]);
void gameMechanics(field board[6][7], char play, int count);
int checkWin(field board[6][7]);
void postGameMenu();
void loadMenu();
void saveGame(char name1[20], char name2[20], char turn);
int numOfFreeFields(field board[6][7]);

int main() {
	//field board[6][7];
	mainMenu();

	return 0;
}

void mainMenu() {
	printf("    \n     Connect Four			      \n");
	printf("                                     \n");
	printf("  1. Play new game                   \n");
	printf("  2. Load alredy saved game          \n");			// design of the menu
	printf("  3. Instruction			      \n");
    printf("  4. Exit                          \n");

	printf("  Enter the option: ");
	scanf("%d", &option);

	while (option != 1 && option != 2 && option != 3 && option !=4) {   // if option is not 1/2/3/4 => printf("enter valid option")
		printf("Please enter a valid option: ");
		scanf("%d", &option);
	}
	switch (option) {
	case 1:
		pNames();
		clearBoard(board);
		printBoard(board);   // case 1 => program have to read out name of players, board,count,turn, win and gameMechanics so game can start.
		count = 0;
		turn = 'X';
		win = 0;
		gameMechanics(board, turn, count);
		break;

	case 2:
		loadMenu();   // case2 => loadmenu
		break;

	case 3:
		instruction(); // case3 => instruction
		break;

        case 4:
		exit(0);  // case4 => exit
		break;
	}
}

void pNames() {
	printf("\nName of first player:");    // We ask users to enter their name.
	scanf("%s", name1);
	printf("\nName of second player:");
	scanf("%s", name2);
}

void clearBoard(field board[6][7]) {
	for (int i = 0; i < 6; i++) {                     // We print here 6x7 state z which is |_|.
		for (int j = 0; j < 7; j++) {
			board[i][j].state = 'Z';
		}
	}
}

void printBoard(field board[6][7]) {
	int i, j;
	for (i = 0; i < 6; i++) {       // This is for switching state so we can print case x instead of case z
		for (j = 0; j < 7; j++) {
			switch (board[i][j].state) {
			case 'Z':
				printf("|_|");
				break;
			case 'X':
				printf("|X|");
				break;
			case 'O':
				printf("|O|");
				break;
            case 'W':
                printf("|W|");
                break;
			}
		}
		printf("\n");
	}
}

void gameMechanics(field board[6][7], char turn, int count) {   // This is most important part of game.
	int playerInput, change, i;

	if (turn == 'X') {
        change = 1;
	}
	else {
        change = 2;
	}

	while (count < 42 && win == 0) {    // we have 42 moves 

		do {
            insertColumn:
			printf("Turn for %c, enter the number of column: ", turn);     //We ask user to enter number of column(J)
			scanf("%d", &playerInput);

            if (playerInput == 0) {
                saveGame(name1, name2, turn);  // 0 == savegame
                goto insertColumn;
            }
            if (playerInput == 8) {         // 8 == back to mainmenu
                mainMenu();
            }
			if (playerInput >= 1 && playerInput <= 7 && board[0][playerInput - 1].state == 'Z') break; 
			else printf("Please enter valid/free field\n");
		}while (1);

		for (i = 0; i < 6; i++) {
			if (board[i][playerInput - 1].state == 'Z' && board[i + 1][playerInput - 1].state != 'Z' && i!=6) { 
				board[i][playerInput - 1].state = turn;
				count++;
				break;                                                                  // When we use for example board i - rows and input is 1 , its going to fill column 1 row 1 so && when is colum 1 row 1 taken we fill i+1(row 2). Also i !=6
			}
            else {
				if (i == 5 && board[6][playerInput - 1].state=='Z') {
					board[6][playerInput - 1].state = turn;
					count++;
					break;
				}
			}
		
		}
		win = checkWin(board);
		if (win == 0) {                        // when win is 0 then change 1(State 'x') to 2(state '0')
            printBoard(board);       
            if (change == 1) {
                change = 2;
                turn = 'O';
            }
            else {
                change = 1;
                turn = 'X';
            }
		}

	}(count < 42);
	postGameMenu();   
}

int checkWin(field board[6][7]) {
    int i, j;
    //horizontal
    for (i = 0; i < 6; i++) {
        for(j = 0; j <= 3; j++) {

            if (board[i][j].state != 'Z') {
                if (board[i][j].state == board[i][j+1].state && board[i][j+1].state == board[i][j+2].state && board[i][j+2].state == board[i][j+3].state){ //horizontal (This is actually really simple. If our state is for example 'x' in board(i)(j)(j+1)(j+2)(j+3) we are going change that state to state 'w' and return 1)
                    if(board[i][j].state == 'X') {
                        printf("X is a winner !\n");
                    }
                    else printf("O is a winner!\n");
                    board[i][j].state = 'W';
                    board[i][j+1].state = 'W';
                    board[i][j+2].state = 'W';
                    board[i][j+3].state = 'W';
                    printBoard(board);
                    clearBoard(board);
                    return 1;
                }
            }
        }
    }
    //vertical
    for (j = 0; j < 7; j++){
        for (i = 0; i <= 2; i++) {
            if (board[i][j].state != 'Z') {
                if (board[i][j].state == board[i+1][j].state && board[i+1][j].state == board[i+2][j].state && board[i+2][j].state == board[i+3][j].state){ 
                    if(board[i][j].state == 'X') {
                        printf("X is a winner !\n");
                        
                    }
                    else printf("O is a winner!\n");
                    board[i][j].state = 'W';
                    board[i+1][j].state = 'W';                    // same here but its vertical so its vice versa board(j)(i)(i+1)(i+2)(i+3)

                    board[i+2][j].state = 'W';
                    board[i+3][j].state = 'W';
                    printBoard(board);
                    clearBoard(board);
                    return 1;
                }
            }
        }
    }
    // ascending diagonal
   for (int i = 3; i < 7; i++){
        for (int j = 0; j < 3; j++){
            if (board[i][j].state != 'Z') {
                if (board[i][j].state == board[i-1][j+1].state && board[i-1][j+1].state == board[i-2][j+2].state && board[i-2][j+2].state == board[i-3][j+3].state) {
                    if(board[i][j].state == 'X') {
                        printf("X is a winner !\n");
                    }
                    else printf("O is a winner!\n");
                    board[i][j].state = 'W';
                    board[i-1][j+1].state = 'W';          // for diagonal its more complex but principle is same
                    board[i-2][j+2].state = 'W';
                    board[i-3][j+3].state = 'W';
                    printBoard(board);
                    clearBoard(board);
                    return 1;
                }
            }
        }
    }
    //descending diagonal
    for (int i = 3; i < 7; i++){
        for (int j = 3; j < 6; j++){
            if (board[i][j].state != 'Z') {
                if (board[i][j].state == board[i-1][j-1].state && board[i-1][j-1].state == board[i-2][j-2].state && board[i-2][j-2].state == board[i-3][j-3].state) {
                    if(board[i][j].state == 'X') {
                        printf("X is a winner !\n");
                    }
                    else printf("O is a winner!\n");
                    board[i][j].state = 'W';
                    board[i-1][j-1].state = 'W';
                    board[i-2][j-2].state = 'W';
                    board[i-3][j-3].state = 'W';
                    printBoard(board);
                    clearBoard(board);
                    return 1;
                }
            }
        }
    }
    return 0;
}

void instruction() { 
     int postInstructionOption;                 // menu for instructions

         do {
        printf("  1. Rules of game\n");
        printf("  Enter the option: ");
        scanf("%d", &postInstructionOption);  }
        
        while (postInstructionOption != 1); 

        switch (postInstructionOption) {
        case 1:
            printf("  The Connect 4 Board Game Rules are easy to understand In fact, it is in the name.\n  To win Connect Four,all you have to do is connect four.\n  This can be done horizontally, vertically or diagonally.\n  Each player will drop in one checker piece at a time.\n  This will give you a chance to either build your row, or stop your opponent from getting four in a row.\n  0 == SAVEGAME,\n  8 == BACK TO MAINMENU.\n");
            mainMenu();
            
            break;

    }

      }

void postGameMenu() {
    int postGameOption;

    do {
        printf("1. Start a new game\n");
        printf("2. Go to main menu\n");               // postgamemenu
        printf("Enter an option: ");

        scanf("%d", &postGameOption);

    }while (postGameOption != 1 && postGameOption != 2);

    switch (postGameOption) {
        case 1:
            pNames();
            clearBoard(board);
            printBoard(board);
            count = 0;
            char turn = 'X';
            win = 0;
            gameMechanics(board, turn, count);
            break;

		case 2:
            mainMenu();
            break;
    }
}

int numOfFreeFields(field board[6][7]) {
    int countFF = 0;
  
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++) {                        // we count only state 'z' filds and we get how many free filds we have(countFF++).
            if (board[i][j].state == 'Z') {
                countFF++;
            }
        }
    }

    return countFF;

}

void loadMenu() {
    int i, j, loadOption, searchID, fileID, finder;                        // loadmenu
    char fileTurn, fileName1[20], fileName2[20], searchName[20];
    field fileBoard[6][7];
    FILE *f;

    do {
        printf("\n1. List all saved games\n");
        printf("2. List all saved games for a particular player\n");
        printf("3. Show the board of one of the saved games\n");
        printf("4. Load game\n");
        printf("5. Return to main menu\n");

        printf("Enter an option: ");
        scanf("%d", &loadOption);

        if (loadOption != 1 && loadOption != 2 && loadOption != 3 && loadOption != 4 && loadOption != 5) printf("Please enter a valid option!\n");
    }while(loadOption != 1 && loadOption != 2 && loadOption != 3 && loadOption != 4 && loadOption != 5);

    switch(loadOption) {

    case 1:
        f = fopen("savedgames.txt", "r");
            while(fscanf(f, "%d %s %s %c ", &fileID, fileName1, fileName2, &fileTurn) == 4) {  // We need only to show all saved games that's why is "r"(read). fscanf returns the number of inputs  successfully scanned and stored (4)
                for(i = 0; i < 6; i++){
                        for(j = 0; j < 7; j++){
                            fscanf(f,"%c ", &fileBoard[i][j].state);
                    }
                }
                printf("ID: %d, X name: %s, O name: %s, Number of free fields: %d\n", fileID, fileName1, fileName2, numOfFreeFields(fileBoard)); 
            }
        fclose(f);
        loadMenu();
        break;

    case 2:
        printf("Enter player name to search: ");
        scanf("%s", &searchName);

        f = fopen("savedgames.txt", "r");
            while(fscanf(f, "%d %s %s %c ", &fileID, fileName1, fileName2, &fileTurn) == 4) {
                for(i = 0; i < 6; i++){
                        for(j = 0; j < 7; j++){
                            fscanf(f,"%c ", &fileBoard[i][j].state);
                    }
                }
            if(strcmp(searchName,fileName1) == 0 || strcmp(searchName,fileName2) == 0) {       // Strcmp function is for comparing the first character of each string, if they are equal it continues with following pairs until they are not or terminal 0 is reached.
                printf("ID: %d, X name: %s, O name: %s, Number of free fields: %d\n", fileID, fileName1, fileName2, numOfFreeFields(fileBoard));
            }

    }
    fclose(f);
    loadMenu();
    break;

    case 3:
        while(1){
		        finder = 0; // we define finder = 0
    		    printf("Enter an ID of the game to search: ");
    		    scanf("%d", &searchID);
    		    printf("\n");
    		    f = fopen("savedgames.txt", "r");
                    while(fscanf(f, "%d %s %s %c ", &fileID, fileName1, fileName2, &fileTurn) == 4) {
                        for(i = 0; i < 6; i++){
                            for(j = 0; j < 7; j++){
                                fscanf(f,"%c ", &fileBoard[i][j].state);
                            }
                        }
                    if(searchID == fileID){   // if searchID is equal to fileID we define finder = 1
    		            finder = 1;
    		            printf("X name is: %s, O name is: %s\n", fileName1, fileName2);
        		        for(i = 0; i < 6; i++){
                            for(j = 0; j < 7; j++){
                                fscanf(f,"%c ", &fileBoard[i][j].state);
                            }
                        }
    		            printBoard(fileBoard);  // we fscanfboard and print it
    		            clearBoard(fileBoard);
    		            break;
                        }
                    }
                    if(finder == 0){
    		        printf("We could not find game with that ID, please try again!\n"); // if finder egual to 0 , printf(we could not find game)
                    }else if(finder == 1){
                        fclose(f);
                        break;
                    }
                    fclose(f);

        }
        loadMenu();
        break;

    case 4:
        while(1){
		        finder = 0;
    		    printf("Enter an ID id of a game you would like to load: ");
    		    scanf("%d", &searchID);
    		    putchar('\n');
    		    f=fopen("savedgames.txt", "r");
    		    while(fscanf(f,"%d %s %s %c ", &fileID, fileName1, fileName2, &fileTurn) == 4){
    		        for(i = 0; i < 6; i++){
    		            for(j = 0; j < 7; j++){
    		                fscanf(f,"%c ", &fileBoard[i][j].state);
    		            }
    		        }
    		        if(searchID == fileID){ // strcpy is used to copy one string to another 
    		            finder = 1;
    		            turn = fileTurn;
    		            strcpy(name1, fileName1);
    		            strcpy(name2, fileName2);
        		        for(i = 0; i < 6; i++){
        		            for( j = 0; j < 7; j++){
        		               board[i][j].state = fileBoard[i][j].state;
        		            }
    		            }
    		            count = 42 - numOfFreeFields(board);
    		            break;
    		        }
    		    }
    		    if(finder == 0){
    		        printf("You have entered an non-existing ID, please try again!\n");
    		    }else if(finder == 1){
    		        fclose(f);
    		        break;
    		    }
    		    fclose(f);
		    }

		    printBoard(board);
		    gameMechanics(board, turn, count);    // we dont print clearboard only printboard and gameMechanics so game can continue without chaning the board.

		    break;

    case 5:
        mainMenu();
        break;
    }
}

void saveGame(char name1[20], char name2[20], char turn) {

    int i, j, fileID = 1;
    char fileName1[20], fileName2[20], fileTurn;
    field fileBoard[6][7];
    FILE *f;

    f = fopen("savedgames.txt", "r");
    while(fscanf(f, "%d %s %s %c ", &fileID, fileName1, fileName2, &fileTurn) == 4) {
        for(i = 0; i < 6; i++){
                for(j = 0; j < 7; j++){
                    fscanf(f,"%c ", &fileBoard[i][j].state);
            }
        }
    }
    fclose(f);

    f = fopen("savedgames.txt", "a"); // If file is not existing "a"(appends) is going to create it
    fprintf(f, "%d %s %s %c ", fileID+1, name1, name2, turn);
    for(i = 0; i < 6; i++){
            for(j = 0; j < 7; j++){
                fprintf(f,"%c ", board[i][j].state);
            }
        }
    putc('\n', f); // putc is used for writing a character in file
    fclose(f);

    printf("Game saved successfully Your ID is %d\n", fileID + 1); // fileID+1 so its always different

}
