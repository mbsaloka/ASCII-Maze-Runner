#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define N 20
#define MONSTER 60
#define WALL 110

#define BLUE "\x1b[1m\x1b[94m"
#define RED "\x1b[1m\x1b[91m"
#define ORANGE "\x1b[1m\033[38;5;208m"
#define GREEN "\x1b[1m\033[92m"
#define GRAY "\x1b[90m"
#define YELLOW "\x1b[33m"
#define PURPLE "\033[1;95m"
#define CYAN "\033[36m"
#define BOLD "\x1b[1m"
#define NO_EFFECT "\x1b[0m"
#define HIDE_CURSOR "\e[?25l"
#define SHOW_CURSOR "\e[?25h"
#define CURSOR_UP(n) printf("\033[%dA\r", (n))
#define CURSOR_DOWN(n) printf("\033[%dB\r", (n))
#define CURSOR_LEFT(n) printf("\033[%dD", (n))
#define CURSOR_RIGHT(n) printf("\033[%dC", (n))
#define CLEAR_ROW(n) ({for (int i = 0; i < (n); i++) printf("\033[A\033[2K\r"); })
#define clearScreen() printf("\x1b[2J\x1b[H")

typedef struct player_s {
    int Y, X, gameChar, level, status;
    char color[50];
} Player;

typedef struct scoreboard_s {
    char dateTime[40];
    int level;
} Scoreboard;

Player hero;
Scoreboard scoreboard[101];
int sbIndex = 0;

char grid[N][N], hiddenGrid[N][N];
int cheatToggle = 0;

void generateHiddenGrid() {
    int randRow, randCol, startRow, startCol;
    int pathCount = 0, wallCount = 0, bomCount = 0;
    int loopCheck = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || i == N - 1 || j == 0 || j == N - 1)
                hiddenGrid[i][j] = '#';
            else
                hiddenGrid[i][j] = '?';
        }
    }

    srand(time(NULL));

    if (hero.level == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (((i == (N / 2 - 3) || i == (N / 2 + 3)) && (j > (N / 2 - 6) && j < (N / 2 + 6)))) {
                    hiddenGrid[i][j] = '#';
                }
                if ((j == (N / 2 - 5) || j == (N / 2 + 5)) && (i > (N / 2 - 3) && i < (N / 2 + 3))) {
                    hiddenGrid[i][j] = '#';
                }
                if ((i == N / 2 - 1 || i == N / 2 + 1) && j > N / 2 && j < N) {
                    hiddenGrid[i][j] = '#';
                }

                if (i > (N / 2 - 3) && i < (N / 2 + 3) && j > (N / 2 - 5) && j < (N / 2 + 5)) {
                    hiddenGrid[i][j] = '+';
                } else if (i == N / 2 && j > N / 2 && j < N) {
                    hiddenGrid[i][j] = '+';
                }
            }
        }
        hiddenGrid[N / 2][N - 1] = 'N';
        return;
    } else {
        hero.X = 0;
    }

    startRow = hero.Y;
    startCol = hero.X;

    hiddenGrid[startRow][startCol] = '.';
    while (hero.X < N - 2) {
        int nextRow, nextCol, nextMove;
        nextRow = hero.Y;
        nextCol = hero.X;
        nextMove = rand() % 3;
        switch (nextMove) {
        case 0:  // Ke atas
            nextRow--;
            if (nextRow < 0) nextRow = 0;
            break;
        case 1:  // Ke bawah
            nextRow++;
            if (nextRow >= N) nextRow = N - 1;
            break;
        case 2:  // Ke kanan
            nextCol++;
            if (nextCol >= N) nextCol = N - 1;
            break;
        }

        if (hiddenGrid[nextRow][nextCol] == '?') {
            int visited = 0;
            if (hiddenGrid[nextRow + 1][nextCol] == '.') visited++;
            if (hiddenGrid[nextRow - 1][nextCol] == '.') visited++;
            if (hiddenGrid[nextRow][nextCol + 1] == '.') visited++;

            if (visited <= 1) {
                pathCount++;
                hiddenGrid[nextRow][nextCol] = '.';
                hero.Y = nextRow;
                hero.X = nextCol;
                loopCheck = 0;
            } else {
                loopCheck++;
            }
        } else {
            loopCheck++;
        }

        if (loopCheck > 10) {
            if (hero.X == N - 3) {
                break;
            } else {
                generateHiddenGrid();
                return;
            }
        }
    }
    hiddenGrid[hero.Y][hero.X + 1] = 'N';
    hero.Y = startRow;
    hero.X = startCol;

    while (wallCount < WALL) {
        randRow = rand() % 20;
        randCol = rand() % 20;
        if (hiddenGrid[randRow][randCol] == '?') {
            wallCount++;
            hiddenGrid[randRow][randCol] = '#';
        }
    }

    while (bomCount < MONSTER) {
        randRow = rand() % 20;
        randCol = rand() % 20;
        if (hiddenGrid[randRow][randCol] == '?') {
            bomCount++;
            hiddenGrid[randRow][randCol] = '*';
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (hiddenGrid[i][j] == '?') {
                hiddenGrid[i][j] = '.';
            }
        }
    }
}

void generateGrid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = hiddenGrid[i][j];
            if (grid[i][j] == '.' || grid[i][j] == '*') {
                grid[i][j] = '?';
            }
            if (grid[i][j] == '+') {
                grid[i][j] = '.';
            }
            if (hero.level == 0 && i == N / 2 - 2) {
                printf(NO_EFFECT);
                if (j == 8) grid[i][j] = 'S';
                if (j == 9) grid[i][j] = 'T';
                if (j == 10) grid[i][j] = 'A';
                if (j == 11) grid[i][j] = 'R';
                if (j == 12) grid[i][j] = 'T';
            }
        }
    }
}

char *getDateTime() {
    int day, month, year, hour, minute, second;
    time_t now;
    struct tm *current_time;
    time(&now);
    current_time = localtime(&now);
    day = current_time->tm_mday;
    month = current_time->tm_mon + 1;
    year = current_time->tm_year + 1900;
    hour = current_time->tm_hour;
    minute = current_time->tm_min;
    second = current_time->tm_sec;

    static char dateTime[40];
    sprintf(dateTime, "%02d/%02d/%04d %02d:%02d:%02d", day, month, year, hour, minute, second);
    return dateTime;
}

char getYesNo() {
    char key, c;
    int i = 0;
    while (c != 13) {
        c = getch();
        if (c == 'y' || c == 'n') c -= 32;
        if ((c == 'Y' || c == 'N') && i == 0) {
            printf("%c", c);
            key = c;
            i++;
        } else if (c == 8 && i > 0) {
            printf("%c %c", c, c);
            key = ' ';
            i--;
        }
        if (c == 3) exit(0);
        if (c == 27) {
            printf("\n");
            return 'N';
        }
        if (c == 13) i == 0 ? c = 0 : printf("\n");
    }
    return key;
}

void printGrid(char grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char c = grid[i][j];
            if (cheatToggle && c == '?') c = hiddenGrid[i][j];
            if (i == hero.Y && j == hero.X) c = hero.gameChar;
            if (c == '#') printf(YELLOW);
            if (c == 'N') printf(GREEN);
            if (c == hero.gameChar) {
                (hero.status) ? printf(hero.color) : printf(RED);
            }
            if (c == '?') printf(GRAY);
            if (c == '.') printf(NO_EFFECT);
            if (c == '*') printf(RED);
            printf("%c ", c);
            printf(NO_EFFECT);
        }
        printf("\n");
    }
}

void printPlayer(int pastY, int pastX, int moveY, int moveX) {
    CURSOR_UP(N - pastY);
    if (pastX > 0) CURSOR_RIGHT(pastX * 2);
    printf(". ");

    if (moveY < 0) {
        CURSOR_UP(1);
        CURSOR_RIGHT(pastX * 2);
    } else if (moveY > 0) {
        CURSOR_DOWN(1);
        CURSOR_RIGHT(pastX * 2);
    } else if (moveX < 0) {
        CURSOR_LEFT(4);
    }

    printf("%s%c%s ", hero.color, hero.gameChar, NO_EFFECT);

    CURSOR_DOWN(N - (pastY + moveY));
}

void printMsg(int msgCode) {
    switch (msgCode) {
    case 1:
        printf("Move : WASD");
        break;
    case 2:
        printf("GAME OVER! You Eaten by Monster!\n");
        break;
    default:
        break;
    }
}

int checkWinLose(int y, int x) {
    if (grid[y][x] == 'N') {
        hero.Y = y;
        hero.X = x;
        return 1;
    }
    if (hiddenGrid[y][x] == '*') {
        hero.Y = y;
        hero.X = x;
        return -1;
    }
    return 0;
}

int checkValidMove(int *y, int *x) {
    if (*y < 0) *y = 0;
    if (*y >= N) *y = N - 1;
    if (*x < 0) *x = 0;
    if (*x >= N) *x = N - 1;
    if (grid[*y][*x] == '#') return 0;
    return 1;
}

int move() {
    int nextRow = hero.Y, nextCol = hero.X;
    char moveCode = getch();

    if (moveCode >= 'a' && moveCode <= 'z') moveCode -= 32;

    switch (moveCode) {
    case 'W':
        nextRow--;
        hero.gameChar = '^';
        break;
    case 'A':
        nextCol--;
        hero.gameChar = '<';
        break;
    case 'S':
        nextRow++;
        hero.gameChar = 'v';
        break;
    case 'D':
        nextCol++;
        hero.gameChar = '>';
        break;
    case '1':
        clearScreen();
        cheatToggle = !cheatToggle;
        printGrid(grid);
        printMsg(1);
        printf("\nLEVEL %d", hero.level);
        CURSOR_UP(1);
        break;
    case 27:
        printf("\n\n\nYakin ingin mengakhiri permainan? (Y/N) ");
        char confirm;
        confirm = getYesNo();
        if (confirm == 'Y') return 0;
        CLEAR_ROW(1);
        CURSOR_UP(3);
        break;
    case 3:
        exit(0);
        break;
    }

    if (moveCode == 'W' || moveCode == 'A' || moveCode == 'S' || moveCode == 'D') {
        if (nextCol >= 0) {
            if (checkValidMove(&nextRow, &nextCol)) {
                if (checkWinLose(nextRow, nextCol)) return 0;

                grid[hero.Y][hero.X] = '.';
                grid[nextRow][nextCol] = hero.gameChar;

                printPlayer(hero.Y, hero.X, nextRow - hero.Y, nextCol - hero.X);
                printMsg(1);
                hero.Y = nextRow;
                hero.X = nextCol;
            }
        }
    }

    return 1;
}

void updateScoreboardDB() {
    FILE *outp;
    outp = fopen("scoreboard.bin", "ab");
    fwrite(&scoreboard[sbIndex], sizeof(Scoreboard), 1, outp);
    fclose(outp);
}

void importDB(int *n) {
    FILE *inp;
    inp = fopen("scoreboard.bin", "rb");
    if (inp == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(inp, 0, SEEK_END);
    int fileSize = ftell(inp);
    *n = fileSize / sizeof(Scoreboard);
    rewind(inp);

    const int maxData = 100;
    *n = (*n > maxData) ? maxData : *n;
    fread(scoreboard, sizeof(Scoreboard), *n, inp);
    fclose(inp);
}

int downArrow(int a, int b) {
    return ((a == '\0' || a == 224) && b == 'P');
}

int upArrow(int a, int b) {
    return ((a == '\0' || a == 224) && b == 'H');
}

int chooseOption(char *option[], int length) {
    int code = 0;
    int input, prev;
    for (int i = 0; i < length; i++) {
        printf("  %s\n", option[i]);
    }
    printf("%s", HIDE_CURSOR);
    CURSOR_UP(length);
    printf("%s> %s%s", BLUE, option[0], NO_EFFECT);
    do {
        prev = input;
        input = getch();
        if (input == 'w' || input == 's') input -= 32;
        if (downArrow(prev, input) || upArrow(prev, input) || input == 'W' || input == 'S') {
            printf("\r  %s", option[code]);
            (input == 'P' || input == 'S') ? code++ : code--;
            if (code >= length) {
                code = 0;
                CURSOR_UP(length - 1);
            } else if (code < 0) {
                code = length - 1;
                CURSOR_DOWN(length - 1);
            } else {
                (input == 'P' || input == 'S') ? CURSOR_DOWN(1) : CURSOR_UP(1);
            }
            printf("%s> ", (code == length - 1) ? RED : BLUE);
            printf("%s%s", option[code], NO_EFFECT);
        }

        if (input == 3) {
            printf("%s", SHOW_CURSOR);
            exit(0);
        } else if (input == 27) {
            printf("%s", SHOW_CURSOR);
            return length - 1;
        }
    } while (input != 13);
    printf("%s", SHOW_CURSOR);
    return code;
}

void showScoreboard() {
    int highScore = 0;
    for (int i = 0; i < sbIndex; i++) {
        if (highScore < scoreboard[i].level) highScore = scoreboard[i].level;
    }
    printf("%s%sSCOREBOARD%s\n", YELLOW, BOLD, NO_EFFECT);
    printf("HIGH SCORE : %d\n\n", highScore);

    printf(BOLD);
    printf("Waktu Permainan     | Level\n");
    printf("----------------------------\n");
    printf(NO_EFFECT);
    for (int i = sbIndex - 1; i >= 0; i--) {
        printf("%s | %d\n", scoreboard[i].dateTime, scoreboard[i].level);
    }
    printf("----------------------------\n");
    int code;
    char *option[] = {
        "Reset Scoreboard",
        "Kembali",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        code = chooseOption(option, lengthOption);
        if (code == 0) {
            printf("\nYakin ingin mereset scoreboard? (Y/N) ");
            char yesNo = getYesNo();
            if (yesNo == 'Y') {
                remove("scoreboard.bin");
                FILE *file = fopen("scoreboard.bin", "w");
                sbIndex = 0;
                clearScreen();
                showScoreboard();
                return;
            } else if (yesNo == 'E') {
                exit(0);
            }
        }
    } while (code != lengthOption - 1);
}

void chooseColor() {
    int code;
    char *option[] = {
        "\033[34mBiru\033[0m",       // Biru
        "\033[32mHijau\033[0m",      // Hijau
        "\033[1;95mUngu\033[0m",     // Ungu
        "\033[36mCyan\033[0m",       // Cyan
        "\033[33;91mOrange\033[0m",  // Orange
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    clearScreen();
    printf("%sPilih Warna Karakter!%s\n", BOLD, NO_EFFECT);
    code = chooseOption(option, lengthOption);
    clearScreen();
    switch (code) {
    case 0:
        strcpy(hero.color, BLUE);
        break;
    case 1:
        strcpy(hero.color, GREEN);
        break;
    case 2:
        strcpy(hero.color, PURPLE);
        break;
    case 3:
        strcpy(hero.color, CYAN);
        break;
    case 4:
        strcpy(hero.color, ORANGE);
        break;
    }
}

void playGame() {
    printf(HIDE_CURSOR);
    hero.Y = N / 2;
    hero.X = N / 2;
    hero.level = 0;
    hero.gameChar = '>';
    hero.status = 1;
    do {
        clearScreen();
        generateHiddenGrid();
        generateGrid();
        cheatToggle = 0;
        printGrid(grid);
        printMsg(1);
        printf("\nLEVEL %d\r", hero.level);
        CURSOR_UP(1);

        while (move())
            ;
        if (checkWinLose(hero.Y, hero.X) == 1) {
            hero.level++;
        } else {
            hero.status = 0;
            strcpy(scoreboard[sbIndex].dateTime, getDateTime());
            scoreboard[sbIndex].level = hero.level;
            updateScoreboardDB();
            sbIndex++;
            clearScreen();
            printGrid(hiddenGrid);
            printMsg(2);
            printf("LEVEL %d\n", hero.level);
            printf("%s> Kembali%s", RED, NO_EFFECT);
            while (getch() != 13)
                ;
        }
    } while (hero.status);
}

void menu() {
    int code;
    char *option[] = {
        "START GAME",
        "Pilih Warna Karakter",
        "Lihat Scoreboard",
        "Exit",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        printf("%s!!! ASCII MAZE RUNNER !!!%s\n", BOLD, NO_EFFECT);
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            playGame();
            break;
        case 1:
            chooseColor();
            break;
        case 2:
            showScoreboard();
            break;
        case 3:
            exit(0);
        }
    } while (code != lengthOption - 1);
}

int main() {
    strcpy(hero.color, BLUE);
    printf(HIDE_CURSOR);
    importDB(&sbIndex);
    menu();
}