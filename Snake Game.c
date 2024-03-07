#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define LEBAR 20
#define TINGGI 20
#define ATAS 1
#define BAWAH 2
#define KIRI 3
#define KANAN 4

int i, j, k;
int gameover, score;
int x, y, fruitX, fruitY, tailX[100], tailY[100], nTail;
int direction;
int choice;

struct player {
	char pnama[5];
	int pscore;
};

struct newPlayer {
	char npnama[5];
	int npscore;
};

struct newPlayer np;
struct player p[5];


int splash();
void logic();
void inputName();
void input();
void draw();
void setup();
void loadHighScoresFromFile();
void saveHighScore();
 

int main() {
    setup();

    do {
        splash();
        system("cls");
        
    	switch (choice) {
        	case 1:
            	inputName();
            	while (!gameover) {
                	draw();
                	input();
                	logic();
                	Sleep(100);
            	}
            	np.npscore = score;
            	system("cls");
            	loadHighScoresFromFile();
            	do {
            		printf("Please choose between 1-5: ");
            		scanf("%d", &choice); getchar;
				}while(choice > 5 && choice < 1);
            	saveHighScore();
            	system("cls");
            	break;

        	case 2:
            	loadHighScoresFromFile();
        		printf("Press enter to return to the menu...");
        		getch();
        		system("cls");
            	break;

        	case 3:
            	printf("Goodbye... ^.^\n");
            	break;

        	default:
            	printf("Invalid Choice. Please try Again");
            	break;
    	}
    } while (choice != 3);

    return 0;
}

void saveHighScore(){
    FILE *file = fopen("highscores.txt", "w");
    
    if (file == NULL) {
    	printf("File tidak ditemukan\n");    
	}
	
	for (i = 0; i < 5; i++) {
		if(i == choice-1){
			strcpy(p[i].pnama, np.npnama);
			p[i].pscore = np.npscore;
		}
        fprintf(file, "%s %d\n", p[i].pnama, p[i].pscore);
    }
    fclose(file);
}

void loadHighScoresFromFile() {
    FILE *file = fopen("highscores.txt", "r");

    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    for (i=0; i<5; i++) {
        fscanf(file, "%s %d", p[i].pnama, &p[i].pscore);
    }

    for (i=0; i<5; i++) {
        for (j=0; j<4-i; j++) {
            if (p[j].pscore < p[j + 1].pscore) {
                struct player temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    printf("============ LEADERBOARD ============\n");
    for (i=0; i<5; i++) {
        printf("%d. %s\t%d\n", i + 1, p[i].pnama, p[i].pscore);
    }
    printf("======================================\n");

    fclose(file);
}

void setup() {
    gameover = 0;
    direction = KANAN;
    x = LEBAR / 2;
    y = TINGGI / 2;
    fruitX = rand() % LEBAR;
    fruitY = rand() % TINGGI;
    score = 0;
}

void draw() {
    system("cls");
    system("color 4");
    for (i = 0; i < LEBAR + 2; i++)
        printf("#");
    printf("\n");

    for (i = 0; i < TINGGI; i++) {
        for (j = 0; j < LEBAR; j++) {
            if (j == 0)
                printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else {
                int printFlag = 0;
                for (k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        printFlag = 1;
                    }
                }
                if (printFlag == 0)
                    printf(" ");
            }

            if (j == LEBAR - 1)
                printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < LEBAR + 2; i++)
        printf("#");
    printf("\n");
    printf("Score: %d\n", score);
    printf("q. Quit");
}

void input() {
    if (kbhit()) {
        switch (_getch()) {
            case 'a':
                direction = KIRI;
                break;
            case 'd':
                direction = KANAN;
                break;
            case 'w':
                direction = ATAS;
                break;
            case 's':
                direction = BAWAH;
                break;
            case 'q':
                gameover = 1;
                break;
        }
    }
}

void inputName() {
    do {
        printf("Siapa yang bermain(5 char): ");
        scanf("%s", np.npnama);
    } while (strlen(np.npnama) != 5);
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case KIRI:
            x--;
            break;
        case KANAN:
            x++;
            break;
        case ATAS:
            y--;
            break;
        case BAWAH:
            y++;
            break;
    }

    if (x >= LEBAR) x = 0;
    else if (x < 0) x = LEBAR - 1;
    if (y >= TINGGI) y = 0;
    else if (y < 0) y = TINGGI - 1;

    for (i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % LEBAR;
        fruitY = rand() % TINGGI;
        nTail++;
    }
}

int splash() {
	printf("  /$$$$$$  /$$   /$$  /$$$$$$  /$$   /$$ /$$$$$$$$\n");
	printf(" /$$__  $$ | $$$ | $$ /$$__  $$| $$  /$$/| $$_____/\n");
	printf("| $$  \\__/ | $$$$| $$| $$  \\ $$| $$ /$$/ | $$      \n");
	printf("|  $$$$$$  | $$ $$ $$| $$$$$$$$| $$$$$/  | $$$$$   \n");
	printf(" \\ ___   $$ | $$  $$$$| $$__  $$| $$  $$  | $$__/   \n");
	printf(" /$$ \\  $$| $$\\  $$$| $$  | $$| $$\\  $$ | $$      \n");
	printf("|  $$$$$$/| $$ \\  $$| $$  | $$| $$ \\  $$| $$$$$$$$\n");
	printf(" \\______/ |__/  \\__/|__/  |__/|__/  \\__/|________/\n");
	printf("\n");
	printf("\n");
	
	printf("Menu\n");
	printf("1. Play Snake\n");
    printf("2. View High Scores\n");
    printf("3. Quit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    return choice;
}

