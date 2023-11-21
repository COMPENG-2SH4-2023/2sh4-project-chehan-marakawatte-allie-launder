#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

//bool exitFlag;
objPos border[56];
GameMechs* myGM;
Player* myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    int i,j, index=0;
    //objPos border[56]; initalized globally
    for (i=0;i<10;i++) { //fixme replace 10 with boardsizeX maybe?
        for (j=0;j<20;j++) { 
            if ((i==0) || (i==9) || (j==0) || (j==19)) {
                border[index].setObjPos(j, i, '#'); //border[index] = objPos{j, i, '#'};
                index++;
            }
        }
    }

    myGM = new GameMechs(26, 13); //fixme , are these real dimension?
    myPlayer = new Player(myGM);
}

void GetInput(void)
{

}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);
    int i, j, k=0;
    for (i=0;i<10;i++) {
        for (j=0;j<20;j++) { 
            for(k=0; k<56; k++) {
                if (border[k].x==j && border[k].y==i) {
                    MacUILib_printf("%c", border[k].getSymbol()); // add conversion specifier with MacUILib!!!! or else it won't work
                    break;                   
                }
            }
            if (i!=0 && i!=9) {
                if (j!=0 && j!=19) {
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Board Size: %dx%d, Player Position: <%d,%d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempPos.x, tempPos.y, tempPos.symbol);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
