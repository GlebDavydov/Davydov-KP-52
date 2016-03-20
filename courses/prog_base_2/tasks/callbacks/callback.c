#include<stdio.h>
#include<windows.h>
#include<conio.h>

typedef void (*ConsoleCallback)(short *pox_x, short *pos_y);

typedef void (*GamestyleCB)(ConsoleCallback ccb, short *pos_x, short *pos_y);

void simplegame(ConsoleCallback ccb, short *pos_x, short *pos_y);
void triplemove(ConsoleCallback ccb, short *pos_x, short *pos_y);
void wuttafack(ConsoleCallback ccb, short *pos_x, short *pos_y);

void play(GamestyleCB gscb);

void updateMoveUp(short *pos_x, short *pos_y){
    if((*pos_y)-- == 0){
        *pos_y = 24;
    }
}

void updateMoveLeft(short *pos_x, short *pos_y){
    if((*pos_x)-- == 0){
        *pos_x = 79;
    }
}

void updateMoveRight(short *pos_x, short *pos_y){
    if((*pos_x)++ == 80){
        *pos_x = 0;
    }
}

void updateMoveDown(short *pos_x, short *pos_y){
    if((*pos_y)++ == 25){
        *pos_y = 0;
    }
}

void donothing(short *pos_x, short *pos_y){}

void draw(short *pos_x, short *pos_y){
    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0x0F);
    system("cls");
    pos.X = *pos_x;
    pos.Y = *pos_y;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, 0XEF);
    printf(" ");
    SetConsoleTextAttribute(hConsole, 0x0F);
}

void play(GamestyleCB gscb){
    short pos_y = 1;
    short pos_x = 1;
    char a;
    ConsoleCallback ccb;
    while(a != 27){
        ccb = donothing;
        draw(&pos_x, &pos_y);
        a = getch();
        switch(a){
            case 72:
                ccb = updateMoveUp;
                break;
            case 75:
                ccb = updateMoveLeft;
                break;
            case 77:
                ccb = updateMoveRight;
                break;
            case 80:
                ccb = updateMoveDown;
                break;
            default:
                break;
        }
        gscb(ccb, &pos_x, &pos_y);
    }
}

void simplegame(ConsoleCallback ccb, short *pos_x, short *pos_y){
    ccb(pos_x, pos_y);
}

void triplemove(ConsoleCallback ccb, short *pos_x, short *pos_y){
    ccb(pos_x, pos_y);
    ccb(pos_x, pos_y);
    ccb(pos_x, pos_y);
}

void wuttafack(ConsoleCallback ccb, short *pos_x, short *pos_y){
    ccb(pos_y, pos_x);
}

int main(void){
    GamestyleCB gscb;
    printf("simple game");
    Sleep(1000);
    gscb = simplegame;
    play(gscb);
    printf("triple move");
    Sleep(1000);
    gscb = triplemove;
    play(gscb);
    printf("reversal");
    Sleep(1000);
    gscb = wuttafack;
    play(gscb);
    return 0;
}
